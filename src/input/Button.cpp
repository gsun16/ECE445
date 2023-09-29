#include "Button.h"

namespace input {

  Button::Button(int pin) : pin(pin), currentState(false), previousState(false) {
    pinMode(pin, INPUT_PULLUP);
  }

  bool Button::isPressed() {
    currentState = digitalRead(pin);
    if (currentState != previousState) {
      previousState = currentState;
      return currentState == LOW;
    }
    return false;
  }

}
