#include "Button.h"

namespace input {

Button::Button(int pin) : Switch(), pin(pin) {}

void Button::begin() {
  pinMode(pin, INPUT);
}

void Button::update() {
  bool isNewStatePressed = digitalRead(pin);

  if (isPressed() && !isNewStatePressed) {
    release();
  } else if (isReleased() && isNewStatePressed) {
    press();
  }
}

}
