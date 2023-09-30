#ifndef KEYBOARD_SWITCH_H
#define KEYBOARD_SWITCH_H

#include <Arduino.h>
#include "Switch.h"
#include "../music/Note.h"

namespace input {
  namespace keyboard {

    class KeyboardSwitch : public Switch {
      public:
        KeyboardSwitch(music::Note note, int colPin, int rowPin);

        void begin() override;
        void update() override;

        music::Note getNote();

      private:
        music::Note note;
        int colPin;
        int rowPin;
    };

  }
}

#endif // KEYBOARD_SWITCH_H
