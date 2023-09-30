#ifndef MUSIC_NOTE_H
#define MUSIC_NOTE_H

#include <Arduino.h>

namespace music {

  class Note {
    public:
      Note(String name, double frequency);

      String getName() const;
      double getFrequency() const;
    
    private:
      String name;
      double frequency;
  };

}

#endif // MUSIC_NOTE_H