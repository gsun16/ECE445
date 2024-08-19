#include "PianoKeyboard.h"

PianoKeyboard::PianoKeyboard() {
    // Initialize Keypad after construction
    initializeKeypad();

    // Initialize the keyMap with Note objects
    keySoundMap['1'] = new Note("C1", 32703);
    keySoundMap['2'] = new Note("D1", 29366);
    keySoundMap['3'] = new Note("E1", 26163);
    keySoundMap['4'] = new Note("F1", 24694);
}

PianoKeyboard::~PianoKeyboard() {
    delete keypad; // Clean up dynamically allocated Keypad
    for (int i = 0; i < KEYBOARD_SIZE; ++i) {
        delete keySoundMap[i]; // Clean up Sound objects
    }
}

Sound** PianoKeyboard::getKeySoundMap() const {
    return const_cast<Sound**>(keySoundMap);
}

byte PianoKeyboard::getRows() const {
    return ROWS;
}

byte PianoKeyboard::getCols() const {
    return COLS;
}

char* PianoKeyboard::getKeymap() const {
    return (char*)keys;
}

byte* PianoKeyboard::getRowPins() const {
    return (byte*)rowPins;
}

byte* PianoKeyboard::getColPins() const {
    return (byte*)colPins;
}
