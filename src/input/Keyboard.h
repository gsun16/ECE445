#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Arduino.h>
#include <Keypad.h>
#include "Input.h"

class Keyboard : public Input {
protected:
    Keypad* keypad;

    Keyboard();
    virtual ~Keyboard();

    virtual byte getRows() const = 0;
    virtual byte getCols() const = 0;
    virtual char* getKeymap() const = 0;
    virtual byte* getRowPins() const = 0;
    virtual byte* getColPins() const = 0;
    virtual Sound** getKeySoundMap() const = 0;

    void initializeKeypad();

public:
    Sound* read() override;
};

#endif // KEYBOARD_H
