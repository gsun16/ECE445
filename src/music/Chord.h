#ifndef CHORD_H
#define CHORD_H

#include <Arduino.h>
#include <vector>
#include "Sound.h"
#include "Note.h"

class Chord : public Sound {
private:
    std::vector<Note*> notes;

public:
    Chord(String name, std::vector<Note*> notes);
    ~Chord();

    int getNoteCount() const;
    const std::vector<Note*>& getNotes() const;
};

#endif // CHORD_H
