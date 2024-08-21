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
        {Note::C_4.getId(), Note::D_4.getId()},
        {Note::E_4.getId(), Note::F_4.getId()}
    };
    byte rowPins[ROWS] = {14, 12};
    byte colPins[COLS] = {32, 33};

public:
    PianoKeyboard();
    ~PianoKeyboard();
};

#endif // PIANOKEYBOARD_H
