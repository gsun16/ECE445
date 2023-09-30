#ifndef EVENT_SOURCE_H
#define EVENT_SOURCE_H

#include <vector>
#include "Event.h"
#include "EventListener.h"

namespace event {

  class EventSource {
    public:
      void addEventListener(EventListener* listener) {
        eventListeners.push_back(listener);
      }

      void removeEventListener(EventListener* listener) {
        auto it = std::remove(eventListeners.begin(), eventListeners.end(), listener);
        eventListeners.erase(it, eventListeners.end());
      }

      void dispatchEvent(const Event& event) {
        for (EventListener* listener : eventListeners) {
          listener->onEvent(event);
        }
      }

    private:
      std::vector<EventListener*> eventListeners;
  };

}

#endif // EVENT_SOURCE_H
