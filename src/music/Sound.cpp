#include "Sound.h"

Sound::Sound(Type type, int id, String name) : type(type), id(id), name(name), playing(false) {}

void Sound::start() {
    playing = true;
}

void Sound::stop() {
    playing = false;
}
