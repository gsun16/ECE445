#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include "Event.h"

namespace event {

  class EventListener {
  public:
    virtual void onEvent(const Event& event) = 0;
    virtual ~EventListener() {}
  };
}

#endif // EVENT_LISTENER_H
