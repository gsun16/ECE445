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

void ConsoleOutput::printNoteDetails(Note* note, const String& action) {
    Serial.print(action);
    Serial.print(" Note: Name = ");
    Serial.print(note->getName());
    Serial.print(", Frequency = ");
    Serial.println(note->getFrequency());
}

void ConsoleOutput::printChordDetails(Chord* chord, const String& action) {
    Serial.print(action);
    Serial.print(" Chord: Name = ");
    Serial.println(chord->getName());
    Serial.println("Notes in the chord:");
    
    const std::vector<Note*>& notes = chord->getNotes();
    for (const Note* note : notes) {
        if (note != nullptr) {
            Serial.print(" - ");
            Serial.print(note->getName());
            Serial.print(" with frequency: ");
            Serial.println(note->getFrequency());
        }
    }
}
