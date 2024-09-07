#include "ShiftRegisterInKeyboard.h"

// Array to keep track of key states
bool previousKeyStates[NUM_KEYS] = {false};

ShiftRegisterInKeyboard::ShiftRegisterInKeyboard() : keyPressCallback(nullptr), keyReleaseCallback(nullptr) {}

void ShiftRegisterInKeyboard::begin() {
  // Initialize pins
  pinMode(LOAD_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, INPUT);
  
  // Start with loadPin high
  digitalWrite(LOAD_PIN, HIGH);
  digitalWrite(CLOCK_PIN, LOW);
}

void ShiftRegisterInKeyboard::update() {
  // Load the parallel data from D0-D7 into the shift register
  digitalWrite(LOAD_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(LOAD_PIN, HIGH);
  
  // Read data from the shift register
  byte rawKeyStates = shiftIn(DATA_PIN, CLOCK_PIN, MSBFIRST);

  // Update keyStates array
  bool currentKeyStates[NUM_KEYS] = {false}; // Current states
  for (int i = 0; i < NUM_KEYS; i++) {
    bool currentState = bitRead(rawKeyStates, i) == LOW; // Invert logic: LOW = pressed
    currentKeyStates[i] = currentState;
  }
  
  // Compare the new key states with the previous ones to detect changes
  for (int key = 0; key < NUM_KEYS; key++) {
    if (currentKeyStates[key] != previousKeyStates[key]) {
      if (currentKeyStates[key]) {
        if (keyPressCallback) {
            keyPressCallback(key);
        }
      } else {
        if (keyReleaseCallback) {
            keyReleaseCallback(key);
        }
      }
    }
    // Update the last states
    previousKeyStates[key] = currentKeyStates[key];
  }
}

void ShiftRegisterInKeyboard::onKeyPress(void (*callback)(int key)) {
    keyPressCallback = callback;
}

void ShiftRegisterInKeyboard::onKeyRelease(void (*callback)(int key)) {
    keyReleaseCallback = callback;
}
