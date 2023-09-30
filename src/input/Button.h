#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include "Switch.h"

namespace input {

  class Button : public Switch {
    public:
      Button(int pin);

      void begin() override;
      void update() override;

    private:
      int pin;
  };

} // namespace input

#endif // BUTTON_H
