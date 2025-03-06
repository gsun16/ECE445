#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Arduino.h>

// Define pins for 74HC165 shift register
const int DATA_PIN = 27;
const int DATA_PIN2 = 26;
const int CLOCK_PIN = 25;
const int LOAD_PIN  = 33; // PL (Parallel Load)



const int NUM_KEYS = 16;

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
