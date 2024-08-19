#include "Chord.h"

Chord::Chord(const String& name, Note* notesArray[], int count) : Sound(Sound::Type::CHORD), name(name),  noteCount(noteCount) {
    if (noteCount > MAX_NOTES) {
        noteCount = MAX_NOTES;
    }
    for (int i = 0; i < noteCount; ++i) {
        notes[i] = notesArray[i];
    }
    for (int i = noteCount; i < MAX_NOTES; ++i) {
        notes[i] = nullptr;
    }
}

String Chord::getName() const {
    return name;
}

int Chord::getNoteCount() const {
    return noteCount;
}

Note** Chord::getNotes() {
    return notes;
}

