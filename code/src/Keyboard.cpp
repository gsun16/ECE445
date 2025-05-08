#include "Keyboard.h"

// Array to keep track of button states
bool buttonStates[ROWS][COLS] = {false};

Keyboard::Keyboard() : keyPressCallback(nullptr), keyReleaseCallback(nullptr) {}

void Keyboard::begin() {
    // Set up the control pins for the 74HC595
    pinMode(DATA_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(LATCH_PIN, OUTPUT);
}

void Keyboard::setColumn(int col) {
    uint8_t colValue = ~(1 << col); // Set only the selected column LOW
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, colValue);

    // Latch to transfer the data to output pins
    digitalWrite(LATCH_PIN, LOW);
    digitalWrite(LATCH_PIN, HIGH);

    // Small delay to allow the shift register output to stabilize
    delayMicroseconds(10);
}

void Keyboard::update() {
    /*
    for (int col = 0; col < COLS; col++) {
        // Set the current column to LOW
        setColumn(col);
        // Check each row for a key press
        for (int row = 0; row < ROWS; row++) {
            int currentState = digitalRead(rowPins[row]);
            // Determine the button number (0 to 7 in this case)
            int key = row * COLS + col;
            if (currentState == LOW && !buttonStates[row][col]) {
                // Button was just pressed
                buttonStates[row][col] = true;
                if (keyPressCallback) {
                    keyPressCallback(key);
                }
            } else if (currentState == HIGH && buttonStates[row][col]) {
                // Button was just released
                buttonStates[row][col] = false;
                if (keyReleaseCallback) {
                    keyReleaseCallback(key);
                }
            }
        }
    }
    */
}

void Keyboard::onKeyPress(void (*callback)(int key)) {
    keyPressCallback = callback;
}

void Keyboard::onKeyRelease(void (*callback)(int key)) {
    keyReleaseCallback = callback;
}

int Keyboard::getTotalKeys() {
    return ROWS * COLS;
}