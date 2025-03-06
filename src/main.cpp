#include <AMY-Arduino.h>
#include <ESP_I2S.h>
#include "ShiftRegisterInKeyboard.h"

#define CONFIG_I2S_BCLK  23
#define CONFIG_I2S_LRCLK 1
#define CONFIG_I2S_DIN   22
#define NUM_VOICES        6
#define LED_PIN           2
#define OCTAVE            4
#define MAX_VOICES       10

AMY amy;
I2SClass I2S;
// Keyboard keyboard;
ShiftRegisterInKeyboard keyboard;

// Keep track of the voices being used
struct Voice {
    bool active;
    byte note;
    unsigned long lastUsed;
} voicer[MAX_VOICES];

// Mutex that locks writes to the delta queue
SemaphoreHandle_t xQueueSemaphore;

// Task handles
TaskHandle_t amy_render_handle;
TaskHandle_t amy_fill_buffer_handle;

#define AMY_TASK_COREID                 (1)
#define AMY_RENDER_TASK_COREID          (0)
#define AMY_FILL_BUFFER_TASK_COREID     (1)
#define AMY_RENDER_TASK_PRIORITY        (ESP_TASK_PRIO_MAX - 1)
#define AMY_FILL_BUFFER_TASK_PRIORITY   (ESP_TASK_PRIO_MAX - 1)
#define AMY_TASK_NAME                   "alles_task"
#define AMY_RENDER_TASK_NAME            "alles_r_task"
#define AMY_FILL_BUFFER_TASK_NAME       "alles_fb_task"
#define AMY_TASK_STACK_SIZE             (8 * 1024)
#define AMY_RENDER_TASK_STACK_SIZE      (8 * 1024)
#define AMY_FILL_BUFFER_TASK_STACK_SIZE (8 * 1024)

bool isAnyVoiceActive() {
    for (int i = 0; i < MAX_VOICES; i++) {
        if (voicer[i].active) {
            return true;
        }
    }
    return false;
}

// Finds a free voice. It can be either a 
// voice not in use or the oldest one in use
int getFreeVoice() {
  int voiceIndex = -1;
  long oldestVoiceTimestamp = millis();
  for (int i = 0; i < MAX_VOICES; i++) {
      if (!voicer[i].active) {
          return i; 
      } else if (voicer[i].lastUsed < oldestVoiceTimestamp) {
          oldestVoiceTimestamp = voicer[i].lastUsed;
          voiceIndex = i;
      }
  }
  return voiceIndex;
}

int getOccupiedVoice(byte note) {
    for (int i = 0; i < MAX_VOICES; i++) {
        if (voicer[i].note == note && voicer[i].active) {
            return i;
        }
    }
    return -1;
}

byte getNote(int key) {
    // If key == 0 and OCTAVE == 4, then return 60 == C4
    return (12 * OCTAVE) + 12 + key;
}

void handleVoice(Voice voice, int voiceIndex) {
    struct event e = amy.default_event();
    e.midi_note = voice.note;
    e.velocity = voice.active ? 1 : 0;
    sprintf(e.voices, "%d", voiceIndex); // Convert the int index to char[]
    amy.add_event(e);
}

void noteOn(int key) {
    byte note = getNote(key);
    if (getOccupiedVoice(note) != -1) {
        return; // This note is being played already, ignore it
    }
    if (int freeVoiceIndex = getFreeVoice(); freeVoiceIndex != -1) {
        voicer[freeVoiceIndex].active = true;
        voicer[freeVoiceIndex].note = note;
        handleVoice(voicer[freeVoiceIndex], freeVoiceIndex);
        digitalWrite(LED_PIN, HIGH); // Turn LED ON
    }
}

void noteOff(int key) {
    byte note = getNote(key);
    if (int occupiedVoiceIndex = getOccupiedVoice(note); occupiedVoiceIndex != -1) {
        voicer[occupiedVoiceIndex].active = false;
        handleVoice(voicer[occupiedVoiceIndex], occupiedVoiceIndex);
    }
    if (!isAnyVoiceActive()) {
        digitalWrite(LED_PIN, LOW); // No voice is active, LED OFF
    }
}

// Render the second core
void* esp_render_task(void*) {
  while (1) {
    // Wait for a message that it's time to start rendering
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    // Scan the keyboard
    keyboard.update();
    // Render
    amy.render(0, AMY_OSCS / 2, 1);
    // Tell the other core we're done rendering
    xTaskNotifyGive(amy_fill_buffer_handle);
  }
}

// Make AMY's FABT run forever , as a FreeRTOS task
void* esp_fill_audio_buffer_task(void*) {
  while (1) {
    // Get ready to render
    amy.prepare();
    // Tell the other core to start rendering
    xTaskNotifyGive(amy_render_handle);
    // Render me
    amy.render(AMY_OSCS / 2, AMY_OSCS, 0);
    // Wait for the other core to finish
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    // Write to i2s
    int16_t* block = amy.fill_buffer();
    I2S.write((uint8_t*)block, AMY_BLOCK_SIZE * AMY_NCHANS * AMY_BYTES_PER_SAMPLE);
  }
}

void setup() {
    Serial.begin(115200);

    // Initialize the LED status
    pinMode(LED_PIN, OUTPUT);

    // Initialize the keyboard
    keyboard.begin();
    keyboard.onKeyPress(noteOn);
    keyboard.onKeyRelease(noteOff);

    // I2S
    I2S.setPins(CONFIG_I2S_BCLK, CONFIG_I2S_LRCLK, CONFIG_I2S_DIN, -1, -1);
    I2S.begin(I2S_MODE_STD, AMY_SAMPLE_RATE, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO);

    // Start up AMY
    amy.begin(2,1,1,1);

    // We create a mutex for changing the event queue and pointers as two tasks do it at once
    xQueueSemaphore = xSemaphoreCreateMutex();

    // Create the second core rendering task
    xTaskCreatePinnedToCore((TaskFunction_t)esp_render_task,
                            AMY_RENDER_TASK_NAME,
                            AMY_RENDER_TASK_STACK_SIZE,
                            NULL,
                            AMY_RENDER_TASK_PRIORITY,
                            &amy_render_handle,
                            AMY_RENDER_TASK_COREID);

    // Wait for the render tasks to get going before starting the i2s task
    delay(100);

    // And the fill audio buffer thread, combines, does volume & filters
    xTaskCreatePinnedToCore((TaskFunction_t)esp_fill_audio_buffer_task,
                            AMY_FILL_BUFFER_TASK_NAME,
                            AMY_FILL_BUFFER_TASK_STACK_SIZE,
                            NULL,
                            AMY_FILL_BUFFER_TASK_PRIORITY,
                            &amy_fill_buffer_handle,
                            AMY_FILL_BUFFER_TASK_COREID);

    // Reset the oscillators and create the voices with the selected patch
    amy.reset();
    struct event e = amy.default_event();
    e.load_patch = 180; // 180: DX7 ACCORDION
    strcpy(e.voices, "0,1,2,3,4,5,6,7,8,9"); // Fill the 10 voices with this patch
    amy.add_event(e);
}

void loop() {
  // nothing -- the audio is rendered in the esp_fill_audio_buffer_task
}
