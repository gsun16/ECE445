#include "PianoKeyboard.h"

PianoKeyboard::PianoKeyboard() 
    : Keyboard(ROWS, COLS, (char*)keys, rowPins, colPins, {
        {Note::C_4.getId(), &Note::C_4},
        {Note::D_4.getId(), &Note::D_4},
        {Note::E_4.getId(), &Note::E_4},
        {Note::F_4.getId(), &Note::F_4}
    }) {
}

PianoKeyboard::~PianoKeyboard() {
    for (auto& entry : keySoundMap) {
        delete entry.second; // Delete each Sound object
    }
}
