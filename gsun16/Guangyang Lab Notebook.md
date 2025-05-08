# Lab Notebook - Digital Accordion Project

## Student: \gsun16

## Course: ECE 445 - Senior Design Laboratory

## Semester: Spring 2025

---

### February 3, 2025

**Objective:** Project proposal and define initial design scope.

**Team Members:**

* Guangyang Sun (gsun16)
* Zhuoer Zhang (zhuoer3)
* Hanyu Zhang (hanyu8)

**Problem:**
Traditional accordions are expensive, delicate, and sensitive to environmental conditions. Learning to play is also difficult for beginners. Existing digital accordions cost over \$7,000, making them inaccessible to most hobbyists.

**Proposed Solution:**
Design a low-cost (≤ \$150), modular, and beginner-friendly 12-bass digital accordion that replicates the functionality of traditional instruments while improving affordability and durability.

**Core Subsystems:**

1. **Key Input Subsystem**

   * Matrix-based scanning for detecting 26 treble keys and 12 bass buttons
   * Uses tactile buttons or capacitive sensors
   * Prioritizes responsiveness and modularity

2. **Sound Synthesis Subsystem**

   * Uses MIDI sound bank for authentic accordion sound
   * Supports polyphony and uses either built-in or external DAC
   * Optional use of filters and external storage for MIDI samples

3. **Audio Output Subsystem**

   * 3.5mm audio jack with amplifier for wired output
   * Optional Bluetooth for wireless playback

4. **(Optional) User Interface Subsystem**

   * LED-backlit keys for guidance
   * Playback mode, “lazy mode” for demo playback, sound profile customization
   * Uses OLED/TFT display and RGB LEDs

**Success Criteria:**

* Accurate and responsive key detection
* High-quality accordion sound with minimal distortion
* Functional and clear audio output via wired connection
* Modular hardware with replaceable components
* Total material cost ≤ \$150
* Optional UI features implemented if time allows

---

### February 10, 2025

**Objective:** Explore shift register options for button input subsystem.

**Activity:**

* Researched 74HC165 (parallel-in serial-out) for input.
* Decided to use two 8-bit 74HC165 shift registers to handle 16 buttons.
* Discussed using 74HC595 for output in parallel hardware test.

**Notes:**

* Need to check readout time and debounce time.

---

### February 17, 2025

**Objective:** Build and test a simple shift register circuit.

**Activity:**

* Created a breadboard circuit with a dev board based on a reference project.
* Programmed using Arduino IDE for basic functionality.

---

### February 24, 2025

**Objective:** Begin initial implementation of the custom input scanning system.

**Activity:**

* Wrote `ShiftRegisterInKeyboard` class.
* Implemented shift register reading via bit manipulation:

```cpp
bitVal1 = digitalRead(DATA_PIN);
dataBits1 = (dataBits1 << 1) | (bitVal1 & 1);
```

* Added callback mechanism for keyPress and keyRelease events.

**Debug Notes:**

* Inverted logic observed — LOW indicates button pressed.
* Added logic to debounce via quick successive updates and stability delay.

**Design Decision:**

* Separated state tracking arrays `currentKeyStates[]` and `previousKeyStates[]` for transition detection.

---

### March 2, 2025

**Objective:** Real-time audio rendering and FreeRTOS integration.

**Activity:**

* Implemented two tasks:

  * `esp_render_task()` on Core 0
  * `esp_fill_audio_buffer_task()` on Core 1
* Used `xTaskNotifyGive` and `ulTaskNotifyTake` for synchronization.

**Challenges:**

* Ensured rendering was done in halves and synchronized properly.

---

### March 5, 2025

**Objective:** Breadboard testing with 2 sets of buttons.

**Activity:**

* Completed the breadboard circuit.
* Verified functionality of all 16 keys.
* Observed artifacts due to unstable connections.

---

### March 12, 2025

**Objective:** Enable MIDI-to-chord event translation.

**Activity:**

* Wrote program to convert MIDI note data into custom ChordEvent structure for playback.

---

### March 26, 2025

**Objective:** Begin audio synthesis integration with AMY and ESP32.

**Activity:**

* Configured I2S with:

  * `BCLK = 11`, `LRCLK = 9`, `DIN = 10`
* Integrated `AMY-Arduino` library for FM synthesis.
* Implemented polyphonic voice handling with 16 voices.

**Equation/Logic:**

```
note = (12 * OCTAVE) + 12 + key;
```

* Mapping key index to MIDI note number.

---

### March 31, 2025

**Objective:** PCB assembly.

**Activity:**

* Received PCB shipment.
* Participated in soldering and debugging with teammates.

---

### April 5, 2025

**Objective:** Begin full system testing.

**Activity:**

* Verified 6 keyboards input detection.
* Linked keyboard callbacks to `noteOn()` and `noteOff()`.
* Implemented LED feedback logic for active voice status.

**Testing Results:**

* Able to detect and play multiple notes.
* Confirmed that released notes correctly deallocate voices.

---

### April 10, 2025

**Objective:** Analyze and document debounce timing. Remapped the keys to notes based on bayan accordion layout.

**Activity:**

* Measured signal stabilization delay using oscilloscope.
* Measured mapping using a tuner app.
* Verified debounce time < 7ms.
* Observed \~0.395ms on Scopy.

**Equation:**
Debounce time = time from initial falling edge to stable LOW level

**Screenshot:** *See attached scope capture in figures folder.*

---

### April 24, 2025

**Objective:** Audio quality and SNR validation.

**Activity:**

* Used Audacity to compare synthesized signal with traditional accordion.
* Verified harmonic spectrum with FFT.
* SNR measured > 40dB.

**Observation:**

* AMY output matches expected FM harmonic structure.

---

### May 1, 2025

**Objective:** Verify rendering voice scheduler (RVS).

**Activity:**

* Played 16-note chords using `playChordProgression()`.
* No glitches or audio dropouts observed.

**Design Consideration:**

* Will explore memory and CPU usage under extreme loads.


---

## References

* AMY Synth: [https://github.com/AmySynth/AMY-Arduino](https://github.com/AmySynth/AMY-Arduino)
* 74HC165 Datasheet: TI SN74HC165
* ESP32-S3 Reference Manual
* Audacity SNR Measurement Guide

---



