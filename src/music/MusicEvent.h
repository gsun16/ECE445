#ifndef MUSIC_EVENT_H
#define MUSIC_EVENT_H

#include "../event/Event.h"

#include "Note.h"
#include "Volume.h"

namespace music {

  class NoteEvent : public event::Event {
    public:
      NoteEvent(const Note& note) : note(note) {}
      virtual ~NoteEvent() {}

      const Note& getNote() const {
        return note;
      }

    private:
      Note note;
  };


  class NoteOnEvent : public NoteEvent {
    public:
      NoteOnEvent(const Note& note);
  };


  class NoteOffEvent : public NoteEvent {
    public:
      NoteOffEvent(const Note& note);
  };


  class VolumeChangeEvent : public event::Event {
    public:
      VolumeChangeEvent(Volume volume) : volume(volume) {}

      Volume getVolume() const {
        return volume;
      }

    private:
      Volume volume;
  };

}

#endif // MUSIC_EVENT_H
