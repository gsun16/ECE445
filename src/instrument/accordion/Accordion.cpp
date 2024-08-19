#include "Accordion.h"

Accordion::Accordion(PianoKeyboard* pianoKeyboard, Output* output)
     : pianoKeyboard(pianoKeyboard), output(output) {}

// Accordion::Accordion(PianoKeyboard* pianoKeyboard, Output* output)
//     : pianoKeyboard(pianoKeyboard), stradellaKeyboard(nullptr), output(output) {}

// Accordion::Accordion(PianoKeyboard* pianoKeyboard, StradellaKeyboard* stradellaKeyboard, Output* output)
//     : pianoKeyboard(pianoKeyboard), stradellaKeyboard(stradellaKeyboard), output(output) {}

void Accordion::play() {
    // Process the treble keys
    Sound* pianoSound = pianoKeyboard->read();
    if (pianoSound) {
        output->write(pianoSound);
    }

    /* Process the bass keys
    if (stradellaKeyboard) {
        Sound* stradellaSound = stradellaKeyboard->capture();
        if (stradellaSound) {
            if (stradellaSound->isPlaying()) {
                output->emit(stradellaSound);
            } else {
                output->interrupt(stradellaSound);
            }
        }
    }*/
}
