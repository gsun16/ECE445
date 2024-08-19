#include "Note.h"

Note::Note(String name, int frequency) : Sound(Sound::Type::NOTE, name), frequency(frequency) {}

int Note::getFrequency() const {
    return frequency;
}
