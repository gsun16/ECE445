#include "KeyboardSwitch.h"

namespace input {
  namespace keyboard {

    KeyboardSwitch::KeyboardSwitch(music::Note note, int colPin, int rowPin) : Switch(), note(note), colPin(colPin), rowPin(rowPin) {}

    void KeyboardSwitch::begin() {
        // Initialize any keyboard-specific setup here
    }

    void KeyboardSwitch::update() {
      bool isNewStatePressed = digitalRead(colPin) && digitalRead(rowPin);

      if (isPressed() && !isNewStatePressed) {
        release();
      } else if (isReleased() && isNewStatePressed) {
        press();
      }
    }

    music::Note KeyboardSwitch::getNote() {
        return note;
    }

  }
}
