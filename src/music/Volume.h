#ifndef MUSIC_VOLUME_H
#define MUSIC_VOLUME_H

#include <Arduino.h>

namespace music {

  class Volume {
    public:
      static const int MIN_VOLUME = 0;
      static const int MAX_VOLUME = 127;

      Volume(int value);

      int getValue() const;
    
    private:
      int value;
  };

}

#endif // MUSIC_VOLUME_H