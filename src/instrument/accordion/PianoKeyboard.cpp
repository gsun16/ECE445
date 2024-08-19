#include "PianoKeyboard.h"

PianoKeyboard::PianoKeyboard() 
    : Keyboard(ROWS, COLS, (char*)keys, rowPins, colPins, {
        {'1', new Note("C1", 32703)},
        {'2', new Note("D1", 29366)},
        {'3', new Note("E1", 26163)},
        {'4', new Note("F1", 24694)}
    }) {
}

PianoKeyboard::~PianoKeyboard() {
    for (auto& entry : keySoundMap) {
        delete entry.second; // Delete each Sound object
    }
}
