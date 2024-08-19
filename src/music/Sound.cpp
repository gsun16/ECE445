#include "Sound.h"

Sound::Sound(Type type) : soundType(type), playing(false) {}

bool Sound::isPlaying() const {
    return playing;
}

void Sound::start() {
    playing = true;
}

void Sound::stop() {
    playing = false;
}

Sound::Type Sound::getType() const {
    return soundType;
}
