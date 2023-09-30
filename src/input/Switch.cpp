#include "Switch.h"

namespace input {

  Switch::Switch() {
    currentState = false;
    previousState = false;
  }

  void Switch::press() {
    previousState = currentState;
    currentState = true;
   }

  void Switch::release() {
    previousState = currentState;
    currentState = false;
  }

  bool Switch::isPressed() {
    return currentState;
  }

  bool Switch::wasPressed() {
    return currentState && !previousState;
  }

  bool Switch::isReleased() {
    return !currentState;
  }

  bool Switch::wasReleased() {
    return !currentState && previousState;
  }

} // namespace input
