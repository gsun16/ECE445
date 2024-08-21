#ifndef SOUND_H
#define SOUND_H

#include <Arduino.h>

class Sound {
public:
    enum Type {
        NOTE,
        CHORD
    };

    Sound(Type type, int id, String name);

    constexpr char getId() const { return id; }
    String getName() const { return name; }
    Type getType() const { return type; }
    bool isPlaying() const { return playing; }

    void start();
    void stop();

private:
    Type type;
    char id;
    String name;
    bool playing;
};

#endif // SOUND_H
