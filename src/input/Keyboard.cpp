#include "Keyboard.h"

Keyboard::Keyboard(byte rows, byte cols, char* keymap, byte* rowPins, byte* colPins, std::map<char, Sound*> keySoundMap)
    : keypad(Keypad(makeKeymap(keymap), rowPins, colPins, rows, cols)), keySoundMap(keySoundMap) {
}

Sound* Keyboard::read() {
    if (keypad.getKeys()) { 
        for (int i = 0; i < LIST_MAX; i++) {
            if (keypad.key[i].stateChanged) {
                char key = keypad.key[i].kchar;
                KeyState state = keypad.key[i].kstate;

                auto it = keySoundMap.find(key);
                Sound* sound = (it != keySoundMap.end()) ? it->second : nullptr;

                if (sound) {
                    if (state == PRESSED) {
                        sound->start();
                    } else if (state == RELEASED) {
                        sound->stop();  
                    } else {
                        return nullptr;
                    }
                    return sound;
                }
            }
        }
    }
    return nullptr;
}
