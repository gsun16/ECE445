#ifndef SOUND_H
#define SOUND_H

#include <Arduino.h>

class Sound {
public:
    enum class Type {
        NOTE,
        CHORD
    };

private:
    Type soundType;
    bool playing;
    
public:
    Sound(Type type);
    virtual ~Sound() = default;

    bool isPlaying() const;
    void start();
    void stop();

    Type getType() const;
};

#endif // SOUND_H
