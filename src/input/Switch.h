#ifndef SWITCH_H
#define SWITCH_H

#include "../event/EventSource.h"

namespace input {

  class Switch : public event::EventSource {
    public:
      Switch();

      void press();
      void release();

      bool isPressed();
      bool wasPressed();
      bool isReleased();
      bool wasReleased();

      virtual void begin();
      virtual void update();

    private:
      bool currentState;
      bool previousState;
      Event
  };

}

#endif // SWITCH_H
