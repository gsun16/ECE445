#include "Chord.h"

Chord::Chord(String name, std::vector<Note*> notesVector)
    : Sound(Sound::Type::CHORD, name), notes(notesVector) {
}

Chord::~Chord() {
    // Optionally, if you need to free Note objects created elsewhere, do it here.
    // For example: delete notes[i]; but be cautious with ownership semantics.
}

int Chord::getNoteCount() const {
    return notes.size();
}

const std::vector<Note*>& Chord::getNotes() const {
    return notes;
}
