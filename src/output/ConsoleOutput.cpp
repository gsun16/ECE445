#include "ConsoleOutput.h"

void ConsoleOutput::write(Sound* sound) {
    if (sound->isPlaying()) {
        Serial.print("Playing");
    } else {
        Serial.print("Interrupting");
    }
    Serial.println();
    printSoundDetails(sound);
}

void ConsoleOutput::printSoundDetails(Sound* sound) {
    switch (sound->getType()) {
        case Sound::Type::NOTE:
            printNoteDetails(static_cast<Note*>(sound));
            break;
        case Sound::Type::CHORD:
            printChordDetails(static_cast<Chord*>(sound));
            break;
        default:
            Serial.println("Unknown sound type.");
            break;
    }
}

void ConsoleOutput::printNoteDetails(Note* note) {
    Serial.print(" Note: Name = ");
    Serial.print(note->getName());
    Serial.print(", Octave = ");
    Serial.print(note->getOctave());
    Serial.print(", Accidental = ");
    Serial.print(note->getAccidental() == Note::FLAT ? "Flat" : 
                  note->getAccidental() == Note::SHARP ? "Sharp" : "None");
    Serial.print(", Frequency = ");
    Serial.println(note->getFrequency());
}

void ConsoleOutput::printChordDetails(Chord* chord) {
    Serial.print(" Chord: Name = ");
    Serial.println(chord->getName());
    Serial.println("Notes in the chord:");

    const std::vector<Note*>& notes = chord->getNotes();
    for (Note* note : notes) {
        if (note != nullptr) {
            Serial.print("\t");
            printNoteDetails(note);
        }
    }
}
