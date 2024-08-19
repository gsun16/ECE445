#include "Sound.h"

Sound::Sound(Type type, String name) : type(type), name(name), playing(false) {}

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
    return type;
}

String Sound::getName() const {
    return name;
}