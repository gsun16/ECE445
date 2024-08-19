#ifndef NOTE_H
#define NOTE_H

#include <Arduino.h>
#include "Sound.h"

class Note : public Sound {
private:
    int frequency;

public:
    Note(String name, int frequency);

    int getFrequency() const;
};

#endif // NOTE_H
