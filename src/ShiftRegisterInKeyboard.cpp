#include "ShiftRegisterInKeyboard.h"

// Array to keep track of key states
bool previousKeyStates[NUM_KEYS] = {false};

ShiftRegisterInKeyboard::ShiftRegisterInKeyboard() : keyPressCallback(nullptr), keyReleaseCallback(nullptr) {}

void ShiftRegisterInKeyboard::begin() {
  // Initialize pins
  pinMode(LOAD_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, INPUT);
  pinMode(DATA_PIN2, INPUT);
  
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
  byte dataBits1 = 0;
  byte dataBits2 = 0;

  for (int i = 0; i < 8; i++) {
    // Read current bit from each data pin
    int bitVal1 = digitalRead(DATA_PIN);
    int bitVal2 = digitalRead(DATA_PIN2);

    // Shift left and add the new bit in the LSB position
    dataBits1 = (dataBits1 << 1) | (bitVal1 & 1);
    dataBits2 = (dataBits2 << 1) | (bitVal2 & 1);

    // Pulse the clock to shift out the next bit
    digitalWrite(CLOCK_PIN, HIGH);
    delayMicroseconds(5);
    digitalWrite(CLOCK_PIN, LOW);
    delayMicroseconds(5);
  }


  // Update keyStates array
  bool currentKeyStates[NUM_KEYS] = {false}; // Current states
  for (int i = 0; i < 8; i++) {
    bool currentState = bitRead(dataBits1, i) == HIGH; // Invert logic: LOW = pressed
    currentKeyStates[i] = currentState;
  }
  for (int j = 8; j < 16; j++) {
    bool currentState = bitRead(dataBits2, j-8) == HIGH; // Invert logic: LOW = pressed
    currentKeyStates[j] = currentState;
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
