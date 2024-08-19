#include "Keyboard.h"

Keyboard::Keyboard() : keypad(nullptr) {
    // Constructor is empty, initialization is deferred
}

Keyboard::~Keyboard() {
    delete keypad;
}

void Keyboard::initializeKeypad() {
    keypad = new Keypad(makeKeymap(getKeymap()), getRowPins(), getColPins(), getRows(), getCols());
}

Sound* Keyboard::read() {
    if (keypad->getKeys()) {
        for (int i = 0; i < LIST_MAX; i++) {
            if (keypad->key[i].stateChanged) {
                char key = keypad->key[i].kchar;
                Sound** soundMap = getKeySoundMap();
                Sound* sound = soundMap[static_cast<unsigned char>(key)];
                if (sound) {
                    if (keypad->key[i].kstate == PRESSED) {
                        sound->start();
                    } else {
                        sound->stop();
                    }
                    return sound;
                }
            }
        }
    }
    return nullptr;
}