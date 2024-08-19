#include "Note.h"

Note::Note(const String& name, int frequency) : Sound(Sound::Type::NOTE), name(name), frequency(frequency) {}

String Note::getName() const {
    return name;
}

int Note::getFrequency() const {
    return frequency;
}
