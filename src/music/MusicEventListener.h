// MusicEventListener.h
#ifndef MUSIC_EVENT_LISTENER_H
#define MUSIC_EVENT_LISTENER_H

#include <Arduino.h>
#include "MusicEvent.h"

namespace music {

  class MusicEventListener {
    public:
      virtual ~MusicEventListener() {}

    virtual void onNoteOnEvent(const NoteOnEvent& event) {
      const Note& note = event.getNote();
      Serial.print("Received Note On - Note: ");
      Serial.println(note.getName());
    }

    virtual void onNoteOffEvent(const NoteOffEvent& event) {
      const Note& note = event.getNote();
      Serial.print("Received Note Off - Note: ");
      Serial.println(note.getName());
    }

    virtual void onVolumeChangeEvent(const VolumeChangeEvent& event) {
      const Volume& volume = event.getVolume();
      Serial.print("Received Volume Chante - Value: ");
      Serial.println(volume.getValue());
    }
  };

}

#endif // MUSIC_EVENT_LISTENER_H
