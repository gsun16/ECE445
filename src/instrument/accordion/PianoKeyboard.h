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

    static const int KEYBOARD_SIZE = ROWS * COLS;
    Sound* keySoundMap[KEYBOARD_SIZE] = {nullptr}; // Initialize the array to map the keys to sounds (notes or chords)

protected:
    byte getRows() const override;
    byte getCols() const override;
    char* getKeymap() const override;
    byte* getRowPins() const override;
    byte* getColPins() const override;
    Sound** getKeySoundMap() const override;

public:
    PianoKeyboard();
    ~PianoKeyboard() override;
};

#endif // PIANOKEYBOARD_H
