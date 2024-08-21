#ifndef CONSOLEOUTPUT_H
#define CONSOLEOUTPUT_H

#include <Arduino.h>
#include "Output.h"
#include "Note.h"
#include "Chord.h"

class ConsoleOutput : public Output {
public:
    void write(Sound* sound) override;

private:
    void printSoundDetails(Sound* sound);
    void printNoteDetails(Note* note);
    void printChordDetails(Chord* chord);
};

#endif // CONSOLEOUTPUT_H
