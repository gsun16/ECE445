
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Arduino.h>

// Pin definitions for 74HC595
/*
//dev
const int DATA_PIN = 27;
const int DATA_PIN2 = 26;
const int CLOCK_PIN = 25;
const int LATCH_PIN = 33;
const int NUM_KEYS = 16;
*/
//s3
const int DATA_PIN = 1;
const int DATA_PIN2 = 2;
const int DATA_PIN3 = 3;
const int DATA_PIN4 = 4;
const int DATA_PIN5 = 5;
const int DATA_PIN6 = 6;

const int CLOCK_PIN = 8;
const int LATCH_PIN = 7;
const int NUM_KEYS = 48;


// Matrix dimensions
const int COLS = 1;
const int ROWS = NUM_KEYS;

// Row and column pins
const int rowPins[ROWS] = {1, 2, 3, 4, 5, 6, 7, 8, 
                        9, 10, 11, 12, 13, 14, 15, 16,
                        17, 18, 19, 20, 21, 22, 23, 24,
                        25, 26, 27, 28, 29, 30, 31, 32,
                        33, 34, 35, 36, 37, 38, 39, 40,
                        41, 42, 43, 44, 45, 46, 47, 48};

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
