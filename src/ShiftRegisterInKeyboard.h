#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Arduino.h>

// Define pins for 74HC165 shift register
const int LOAD_PIN  = 18; // PL (Parallel Load)
const int CLOCK_PIN = 14; // CP (Clock Pulse)
const int DATA_PIN  = 19; // Q7 (Serial Out)

const int NUM_KEYS = 8;

class ShiftRegisterInKeyboard {
public:
    ShiftRegisterInKeyboard();
    void begin();
    void update();
    void onKeyPress(void (*callback)(int key));
    void onKeyRelease(void (*callback)(int key));
private:
    void (*keyPressCallback)(int key);
    void (*keyReleaseCallback)(int key);
};

#endif
