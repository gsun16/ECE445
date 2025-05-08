#include <AMY-Arduino.h>
#include <ESP_I2S.h>
#include "ShiftRegisterInKeyboard.h"

// s3 config
/*
#define CONFIG_I2S_BCLK  11
#define CONFIG_I2S_LRCLK 9
#define CONFIG_I2S_DIN   10
*/
#define vin 48
#define gnd 47
#define CONFIG_I2S_LRCLK 46
#define CONFIG_I2S_DIN   45
#define CONFIG_I2S_BCLK  42
#define CONFIG_I2S_SCK  41



#define NUM_VOICES        6
#define LED_PIN           17
#define MAX_VOICES       16

AMY amy;
I2SClass I2S;
ShiftRegisterInKeyboard keyboard;

struct Voice {
    bool active;
    byte note;
    unsigned long lastUsed;
} voicer[MAX_VOICES];

SemaphoreHandle_t xQueueSemaphore;
TaskHandle_t amy_render_handle;
TaskHandle_t amy_fill_buffer_handle;

// Key mapping
byte myArray[48] = {
  69, 66, 63, 60, 100, 101, 102, 103,
  81, 78, 75, 72, 104, 105, 106, 107,
  58, 61, 64, 67, 59, 62, 65, 68,
  70, 73, 76, 79, 71, 74, 77, 80,
  200, 201, 202, 203, 75, 70, 65, 60,
  204, 205, 206, 207, 55, 50, 45, 40
};

bool isAnyVoiceActive() {
    for (int i = 0; i < MAX_VOICES; i++) {
        if (voicer[i].active) return true;
    }
    return false;
}

int getFreeVoice() {
    int voiceIndex = -1;
    long oldest = millis();
    for (int i = 0; i < MAX_VOICES; i++) {
        if (!voicer[i].active) return i;
        if (voicer[i].lastUsed < oldest) {
            oldest = voicer[i].lastUsed;
            voiceIndex = i;
        }
    }
    return voiceIndex;
}

int getOccupiedVoice(byte note) {
    for (int i = 0; i < MAX_VOICES; i++) {
        if (voicer[i].note == note && voicer[i].active) return i;
    }
    return -1;
}

byte getNote(int key) {
    if (key < 0 || key >= 48) return 0;
    return myArray[key];
}

void handleVoice(Voice voice, int voiceIndex) {
    struct event e = amy.default_event();
    e.midi_note = voice.note;
    e.velocity = voice.active ? 1 : 0;
    sprintf(e.voices, "%d", voiceIndex);
    amy.add_event(e);
}

void noteOnKeyCode(byte note) {
    if (getOccupiedVoice(note) != -1) return;
    int freeVoiceIndex = getFreeVoice();
    if (freeVoiceIndex != -1) {
        voicer[freeVoiceIndex].active = true;
        voicer[freeVoiceIndex].note = note;
        handleVoice(voicer[freeVoiceIndex], freeVoiceIndex);
        digitalWrite(LED_PIN, HIGH);
    }
}

void noteOn(int key) {
    byte code = getNote(key);
    if (code < 100) {
        noteOnKeyCode(code);
    } else if (code < 200) {
        // Function keys
        if (code == 100) {
            // Example: Play a chord directly
            byte chord[] = {60, 64, 67};
            //for (byte n : chord) noteOnKeyCode(n);
        }
    } else {
        // Chord keys
        if (code == 200) {
            byte chord[] = {60, 64, 67};
            for (byte n : chord) noteOnKeyCode(n);
        } else if (code == 201) {
            byte chord[] = {62, 65, 69};
            for (byte n : chord) noteOnKeyCode(n);
        } else if (code == 202) {
            byte chord[] = {63, 67, 70};
            for (byte n : chord) noteOnKeyCode(n);
        } else if (code == 203) {
            byte chord[] = {65, 69, 72};
            for (byte n : chord) noteOnKeyCode(n);
        } else if (code == 204) {
            byte chord[] = {60, 64, 67};
            for (byte n : chord) noteOnKeyCode(n);
        } else if (code == 205) {
            byte chord[] = {62, 65, 69};
            for (byte n : chord) noteOnKeyCode(n);
        } else if (code == 206) {
            byte chord[] = {63, 67, 70};
            for (byte n : chord) noteOnKeyCode(n);
        } else if (code == 207) {
            byte chord[] = {65, 69, 72};
            for (byte n : chord) noteOnKeyCode(n);
        } 

    }
}

void noteOff(int key) {
    byte code = getNote(key);

    if (code < 100) {
        // 普通note
        int occupiedVoiceIndex = getOccupiedVoice(code);
        if (occupiedVoiceIndex != -1) {
            voicer[occupiedVoiceIndex].active = false;
            handleVoice(voicer[occupiedVoiceIndex], occupiedVoiceIndex);
        }
    } else if (code >= 200) {
        // 是和弦键，手动释放所有chord音
        switch (code) {
            case 200: {
                byte chord[] = {60, 64, 67};
                for (byte n : chord) {
                    int idx = getOccupiedVoice(n);
                    if (idx != -1) {
                        voicer[idx].active = false;
                        handleVoice(voicer[idx], idx);
                    }
                }
                break;
            }
            case 201: {
                byte chord[] = {62, 65, 69};
                for (byte n : chord) {
                    int idx = getOccupiedVoice(n);
                    if (idx != -1) {
                        voicer[idx].active = false;
                        handleVoice(voicer[idx], idx);
                    }
                }
                break;
            }
            case 202: {
                byte chord[] = {63, 67, 70};
                for (byte n : chord) {
                    int idx = getOccupiedVoice(n);
                    if (idx != -1) {
                        voicer[idx].active = false;
                        handleVoice(voicer[idx], idx);
                    }
                }
                break;
            }
            case 203: {
                byte chord[] = {65, 69, 72};
                for (byte n : chord) {
                    int idx = getOccupiedVoice(n);
                    if (idx != -1) {
                        voicer[idx].active = false;
                        handleVoice(voicer[idx], idx);
                    }
                }
                break;
            }
            case 204: {
                byte chord[] = {60, 64, 67};
                for (byte n : chord) {
                    int idx = getOccupiedVoice(n);
                    if (idx != -1) {
                        voicer[idx].active = false;
                        handleVoice(voicer[idx], idx);
                    }
                }
                break;
            }
            case 205: {
                byte chord[] = {62, 65, 69};
                for (byte n : chord) {
                    int idx = getOccupiedVoice(n);
                    if (idx != -1) {
                        voicer[idx].active = false;
                        handleVoice(voicer[idx], idx);
                    }
                }
                break;
            }
            case 206: {
                byte chord[] = {63, 67, 70};
                for (byte n : chord) {
                    int idx = getOccupiedVoice(n);
                    if (idx != -1) {
                        voicer[idx].active = false;
                        handleVoice(voicer[idx], idx);
                    }
                }
                break;
            }
            case 207: {
                byte chord[] = {65, 69, 72};
                for (byte n : chord) {
                    int idx = getOccupiedVoice(n);
                    if (idx != -1) {
                        voicer[idx].active = false;
                        handleVoice(voicer[idx], idx);
                    }
                }
                break;
            }
            default:
                break;
        }
    }

    if (!isAnyVoiceActive()) {
        digitalWrite(LED_PIN, LOW);
    }
}


void* esp_render_task(void*) {
    while (1) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        keyboard.update();
        amy.render(0, AMY_OSCS / 2, 1);
        xTaskNotifyGive(amy_fill_buffer_handle);
    }
}

void* esp_fill_audio_buffer_task(void*) {
    while (1) {
        amy.prepare();
        xTaskNotifyGive(amy_render_handle);
        amy.render(AMY_OSCS / 2, AMY_OSCS, 0);
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        int16_t* block = amy.fill_buffer();
        I2S.write((uint8_t*)block, AMY_BLOCK_SIZE * AMY_NCHANS * AMY_BYTES_PER_SAMPLE);
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    pinMode(vin, OUTPUT);
    digitalWrite(vin, HIGH);
    pinMode(gnd, OUTPUT);
    digitalWrite(gnd, LOW);



    keyboard.begin();
    keyboard.onKeyPress(noteOn);
    keyboard.onKeyRelease(noteOff);

    I2S.setPins(CONFIG_I2S_BCLK, CONFIG_I2S_LRCLK, CONFIG_I2S_DIN, -1, -1);
    I2S.begin(I2S_MODE_STD, AMY_SAMPLE_RATE, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO);

    amy.begin(2,1,1,1);
    amy.reset();
    struct event e = amy.default_event();
    e.load_patch = 180;
    strcpy(e.voices, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15");
    amy.add_event(e);

    xQueueSemaphore = xSemaphoreCreateMutex();

    xTaskCreatePinnedToCore((TaskFunction_t)esp_render_task, "alles_r_task", 8192, NULL, ESP_TASK_PRIO_MAX - 1, &amy_render_handle, 0);
    delay(100);
    xTaskCreatePinnedToCore((TaskFunction_t)esp_fill_audio_buffer_task, "alles_fb_task", 8192, NULL, ESP_TASK_PRIO_MAX - 1, &amy_fill_buffer_handle, 1);
}

void loop() {
    // Nothing here, work is done in FreeRTOS tasks
}
