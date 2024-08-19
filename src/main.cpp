#include <Arduino.h>
#include "Accordion.h"
#include "PianoKeyboard.h"
#include "ConsoleOutput.h"

Accordion* accordion;

void setup() {
    Serial.begin(115200);

    // Set up PianoKeyboard
    PianoKeyboard* piano = new PianoKeyboard();
    
    // Set up ConsoleOutput
    ConsoleOutput* consoleOutput = new ConsoleOutput();

    // Initialize the accordion with single input/output
    accordion = new Accordion(piano, consoleOutput);
}

void loop() {
    accordion->play();
}
