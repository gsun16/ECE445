#include "ShiftRegisterInKeyboard.h"

// Array to keep track of key states
bool previousKeyStates[NUM_KEYS] = {false};

ShiftRegisterInKeyboard::ShiftRegisterInKeyboard() : keyPressCallback(nullptr), keyReleaseCallback(nullptr) {}

void ShiftRegisterInKeyboard::begin() {
  // Initialize pins
  pinMode(LOAD_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  for (int i = 0; i < 6; i++) {
    pinMode(DATA_PINS[i], INPUT);
}
  // Start with loadPin high
  digitalWrite(LOAD_PIN, HIGH);
  digitalWrite(CLOCK_PIN, LOW);
}

void ShiftRegisterInKeyboard::update() {
  digitalWrite(LOAD_PIN, LOW);
  delayMicroseconds(1);
  digitalWrite(LOAD_PIN, HIGH);

  byte dataBits[6] = {0};

  for (int i = 0; i < 8; i++) { // 8 bits
    for (int j = 0; j < 6; j++) { // 6 shift registers
      int bitVal = digitalRead(DATA_PINS[j]);
      dataBits[j] = (dataBits[j] << 1) | (bitVal & 1);
    }
    digitalWrite(CLOCK_PIN, HIGH);
    delayMicroseconds(1);
    digitalWrite(CLOCK_PIN, LOW);
    delayMicroseconds(1);
  }

  bool currentKeyStates[NUM_KEYS] = {false};

  for (int byteIndex = 0; byteIndex < 6; byteIndex++) {
    for (int bitIndex = 0; bitIndex < 8; bitIndex++) {
      int key = byteIndex * 8 + bitIndex;
      bool currentState = bitRead(dataBits[byteIndex], bitIndex) == HIGH;
      currentKeyStates[key] = currentState;
    }
  }

  for (int key = 0; key < NUM_KEYS; key++) {
    if (currentKeyStates[key] != previousKeyStates[key]) {
      if (currentKeyStates[key]) {
        if (keyPressCallback) keyPressCallback(key);
      } else {
        if (keyReleaseCallback) keyReleaseCallback(key);
      }
    }
    previousKeyStates[key] = currentKeyStates[key];
  }
}


void ShiftRegisterInKeyboard::onKeyPress(void (*callback)(int key)) {
    keyPressCallback = callback;
}

void ShiftRegisterInKeyboard::onKeyRelease(void (*callback)(int key)) {
    keyReleaseCallback = callback;
}
