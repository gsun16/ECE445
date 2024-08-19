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
    Type type;
    String name;
    bool playing;
    
public:
    Sound(Type type, String name);
    virtual ~Sound() = default;

    bool isPlaying() const;
    void start();
    void stop();

    Type getType() const;
    String getName() const;
};

#endif // SOUND_H
