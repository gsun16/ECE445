#ifndef PIANOKEYBOARD_H
#define PIANOKEYBOARD_H

#include <Arduino.h>
#include <Keypad.h>
#include "Keyboard.h"
#include "Note.h"

class PianoKeyboard : public Keyboard {
private:
    static const byte ROWS = 2;
    static const byte COLS = 2;
    char keys[ROWS][COLS] = {
        {'1', '2'},
        {'3', '4'}
    };
    byte rowPins[ROWS] = {22, 23};
    byte colPins[COLS] = {25, 26};

public:
    PianoKeyboard();
    ~PianoKeyboard();
};

#endif // PIANOKEYBOARD_H
