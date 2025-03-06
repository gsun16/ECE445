#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Arduino.h>

// Pin definitions for 74HC595
const int DATA_PIN = 27;
const int DATA_PIN2 = 26;
const int CLOCK_PIN = 25;
const int LATCH_PIN = 33;
const int NUM_KEYS = 16;

// Matrix dimensions
const int COLS = 1;
const int ROWS = NUM_KEYS;

// Row and column pins
const int rowPins[ROWS] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

// Array to keep track of button states
extern bool buttonStates[ROWS][COLS];

class Keyboard {
public:
    Keyboard();
    void begin();
    void update();
    void onKeyPress(void (*callback)(int key));
    void onKeyRelease(void (*callback)(int key));
    int getTotalKeys();
private:
    void setColumn(int col);
    void (*keyPressCallback)(int key);
    void (*keyReleaseCallback)(int key);
};

#endif
