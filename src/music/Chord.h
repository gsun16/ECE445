#ifndef CHORD_H
#define CHORD_H

#include <Arduino.h>
#include "Sound.h"
#include "Note.h"

class Chord : public Sound {
private:
    static const int MAX_NOTES = 4;
    String name;
    Note* notes[MAX_NOTES];
    int noteCount;

public:
    Chord(const String& name, Note* notesArray[], int count);
    ~Chord() = default;

    String getName() const;
    int getNoteCount() const;
    Note** getNotes();
};

#endif // CHORD_H
