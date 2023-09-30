#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../InputChannel.h"

namespace input {
  namespace keyboard {

    class Keyboard : public InputChannel {
      public:
        Keyboard();
        void read() override = 0;
    };

  }
}

#endif // KEYBOARD_H
