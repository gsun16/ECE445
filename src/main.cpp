#include <Arduino.h>
#include "Accordion.h"
#include "PianoKeyboard.h"
#include "ConsoleOutput.h"

Accordion* accordion;

void setup() {
    Serial.begin(9600);

    PianoKeyboard* piano = new PianoKeyboard();
    ConsoleOutput* consoleOutput = new ConsoleOutput();

    accordion = new Accordion(piano, consoleOutput);
}

void loop() {
    accordion->play();
}
