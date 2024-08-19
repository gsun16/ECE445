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
    void printNoteDetails(Note* note, const String& action);
    void printChordDetails(Chord* chord, const String& action);
};

#endif // CONSOLEOUTPUT_H
