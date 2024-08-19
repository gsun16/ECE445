#ifndef ACCORDION_H
#define ACCORDION_H

#include <Arduino.h>
#include "PianoKeyboard.h"
#include "Output.h"

class Accordion {
private:
    PianoKeyboard* pianoKeyboard;
    // StradellaKeyboard* stradellaKeyboard;
    Output* output;

public:
    Accordion(PianoKeyboard* pianoKeyboard, Output* output);
    // Accordion(PianoKeyboard* pianoKeyboard, StradellaKeyboard* stradellaKeyboard, Output* output);

    void play();
};

#endif // ACCORDION_H
