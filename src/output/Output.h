#ifndef OUTPUT_H
#define OUTPUT_H

#include <Arduino.h>
#include "Sound.h"

class Output {
public:
    virtual void write(Sound* sound) = 0;
};

#endif // OUTPUT_H
