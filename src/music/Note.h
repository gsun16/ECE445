#ifndef NOTE_H
#define NOTE_H

#include <Arduino.h>
#include "Sound.h"

class Note : public Sound {
private:
    String name;
    int frequency;

public:
    Note(const String& name, int frequency);
    ~Note() = default;

    String getName() const;
    int getFrequency() const;
};

#endif // NOTE_H
