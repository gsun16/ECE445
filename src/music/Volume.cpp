#include "Volume.h"

namespace music {

  Volume::Volume(int value) : value(value) {
    if (value < MIN_VOLUME) {
      this->value = MIN_VOLUME;
    } else if (value > MAX_VOLUME) {
      this->value = MAX_VOLUME;
    }
  }

  int Volume::getValue() const {
    return value;
  }

} // namespace music
