#ifndef INPUT_BUTTON_H
#define INPUT_BUTTON_H

#include <Arduino.h>

namespace input {

  class Button {

    public:
        Button(int pin);
        bool isPressed();

    private:
        int pin;
        bool currentState;
        bool previousState;
    };

}

#endif