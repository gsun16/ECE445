#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Arduino.h>

// Pin definitions for 74HC595
const int DATA_PIN = 19;
const int CLOCK_PIN = 5;
const int LATCH_PIN = 18;

// Matrix dimensions
const int COLS = 4;
const int ROWS = 2;

// Row and column pins
const int rowPins[ROWS] = {12, 14};

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
