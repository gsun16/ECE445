#include "ConsoleOutput.h"

void ConsoleOutput::write(Sound* sound) {
    if (sound->isPlaying()) {
        switch (sound->getType()) {
            case Sound::Type::NOTE:
                printNoteDetails(static_cast<Note*>(sound), "Playing");
                break;
            case Sound::Type::CHORD:
                printChordDetails(static_cast<Chord*>(sound), "Playing");
                break;
            default:
                Serial.println("Unknown sound type.");
                break;
        }
    } else {
        switch (sound->getType()) {
            case Sound::Type::NOTE:
                printNoteDetails(static_cast<Note*>(sound), "Interrupting");
                break;
            case Sound::Type::CHORD:
                printChordDetails(static_cast<Chord*>(sound), "Interrupting");
                break;
            default:
                Serial.println("Unknown sound type.");
                break;
        }
    }
}

// Private method to print note details
void ConsoleOutput::printNoteDetails(Note* note, const String& action) {
    Serial.print(action);
    Serial.print(" Note: Name = ");
    Serial.print(note->getName());
    Serial.print(", Frequency = ");
    Serial.println(note->getFrequency());
}

// Private method to print chord details
void ConsoleOutput::printChordDetails(Chord* chord, const String& action) {
    Serial.print(action);
    Serial.print(" Chord: Name = ");
    Serial.println(chord->getName());
    Serial.println("Notes in the chord:");
    Note** notes = chord->getNotes();
    for (int i = 0; i < chord->getNoteCount(); ++i) {
        if (notes[i] != nullptr) {
            Serial.print(" - ");
            Serial.print(notes[i]->getName());
            Serial.print(" with frequency: ");
            Serial.println(notes[i]->getFrequency());
        }
    }
}
