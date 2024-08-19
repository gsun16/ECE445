#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Arduino.h>
#include <Keypad.h>
#include <map>
#include "Input.h"

class Keyboard : public Input {
protected:
    Keypad keypad;
    std::map<char, Sound*> keySoundMap;

    Keyboard(byte rows, byte cols, char* keymap, byte* rowPins, byte* colPins, std::map<char, Sound*> keySoundMap);

public:
    Sound* read() override;
};

#endif // KEYBOARD_H
