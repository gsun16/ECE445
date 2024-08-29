#include <Arduino.h>
#include "Keyboard.h"
#include "AudioTools.h"
#include "StkAll.h"

// Define constants
const float AMPLITUDE = 64.0;
const int GROUP = 0;

// Create instances of the audio components
I2SStream i2s;
ArdStreamOut output(i2s, 1);
Clarinet clarinet(440); // Create a clarinet instance
Voicer voicer;
Keyboard keyboard;

// Define key press and release handlers
int getNote(int key) {
    return key + 60;
}

void noteOn(int key) {
    int note = getNote(key);

    Serial.print("Note ");
    Serial.print(note);
    Serial.print(" ON at voice ");
    Serial.println(key);

    voicer.noteOn(note, AMPLITUDE, key);
}

void noteOff(int key) {
    int note = getNote(key);

    Serial.print("Note ");
    Serial.print(note);
    Serial.print(" OFF at voice ");
    Serial.println(key);
    voicer.noteOff(note, AMPLITUDE, key);
}

void setup() {
    Serial.begin(115200);

    // Initialize the keyboard
    keyboard.begin();
    keyboard.onKeyPress(noteOn);
    keyboard.onKeyRelease(noteOff);

    // Add the clarinets to the voicer
    for (int i = 0; i < keyboard.getTotalKeys(); i++) {
        voicer.addInstrument(&clarinet, i);
    }

    // Configure the audio output
    auto cfg = i2s.defaultConfig(TX_MODE);
    cfg.bits_per_sample = 16;
    cfg.sample_rate = Stk::sampleRate();
    cfg.channels = 1;
    cfg.pin_bck = 26;
    cfg.pin_ws = 25;
    cfg.pin_data = 22;
    i2s.begin(cfg);
}

void loop() {
    // Update keyboard and process audio
    keyboard.update();
    output.tick(voicer.tick());
}
