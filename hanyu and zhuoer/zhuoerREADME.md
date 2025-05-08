# Digital Accordion Project Lab Notebook

This README documents the project development process through key milestones. Each entry includes the date, objectives, records of activities, and figures for reference.

## Date: 2/11

**Objective:**  
Zhuoer, Henry, and Guangyang created the first mock diagram illustrating the system's functional flow.

**Record of what was done:**

- Designed a high-level mock diagram to represent input-output relationships.
- Defined system inputs: accordion keys, chord keys, mode buttons, and power.
- Defined system outputs: synthesized accordion sound produced by sound module and speaker.

**Fig. 13:** Mock Diagram

---

## Date: 2/17

**Objective:**  
Finalize component selection and translate mock diagram into a block diagram.

**Record of what was done:**

- Zhuoer, Henry, and Guangyang selected components to be used in the system.
- Converted the mock diagram into a detailed block diagram.
- Established system architecture to guide schematic and PCB layout design.

**Fig. 14:** Block Diagram

---

## Date: 2/25

**Objective:**  
Complete the PCB schematic design for the keyboard.

**Record of what was done:**

- Zhuoer and Henry collaborated to design the keyboard schematic in KiCad.
- Implemented matrix scanning with 8 columns × 5 rows for 40 keys.
- Connected rows to 74HC595 shift register outputs; connected columns to ESP32 GPIO via multiplexer inputs.
- Verified compatibility with Cherry MX switch footprints.

**Key decisions:**

- Selected 10kΩ pull-down resistors on column lines to prevent floating inputs.

**Fig. 1:** Schematic diagram of keyboard circuit

---

## Date: 3/2

**Objective:**  
Finish the PCB layout for the keyboard.

**Record of what was done:**

- Zhuoer and Henry completed component placement and routing in KiCad.
- Minimized trace lengths for reduced capacitance.
- Routed all traces on top copper layer; added ground plane on bottom layer for EMI reduction.
- Verified clearance per IPC-2221 minimums for 5V operation.

**Problems/decisions:**

- Increased trace width from 8 mil to 12 mil for durability.
- Relocated decoupling capacitor closer to shift register power pins for improved stability.

**Fig. 2:** Completed keyboard PCB layout

---

## Date: 3/2 (PM)

**Objective:**  
Complete the PCB layout for the control board (ESP32 + DAC) and resolve pin size issue in KiCad.

**Record of what was done:**

- Zhuoer and Guangyang completed the control board layout.
- Identified and fixed ESP32 footprint pin size mismatch in KiCad library editor.
- Verified adequate component spacing for heat dissipation.
- Added 3.3V and 5V power planes; passed DRC with no net shorts.

**Figures:**

- **Fig. 3:** Control board schematic
- **Fig. 4:** Final corrected PCB layout
- **Fig. 5:** Initial layout with pin size error

---

## Date: 3/31

**Objective:**  
Receive first batch of PCB boards and begin assembly.

**Record of what was done:**

- Zhuoer and Henry received the manufactured PCBs.
- Discovered through-hole shift registers needed bending to fit surface-mount pads.
- Bent 74HC595 IC leads to flatten and solder onto pads.
- Assembled and soldered buttons and ICs onto two keyboard PCBs.

**Figures:**

- **Fig. 6:** Unpopulated keyboard PCB
- **Fig. 7:** Shift register lead bending process
- **Fig. 8:** Partially assembled keyboard PCB

---

## Date: 4/8

**Objective:**  
Complete soldering for remaining keyboards; check for errors.

**Record of what was done:**

- Zhuoer and Henry soldered remaining keyboard PCBs.
- Detected potential soldering issue; flagged for future debugging.

---

## Date: 4/15

**Objective:**  
Debug and correct connection issue on keyboard PCB.

**Record of what was done:**

- Zhuoer used a multimeter to trace a short between row 3 and row 4.
- Found solder bridge at pin 6 of shift register; removed excess solder with solder wick.
- Verified continuity for all rows and columns after correction.

**Fig. 9:** Debug diagram showing faulty connection and correction

---

## Date: 4/25

**Objective:**  
Test keyboard connections using external ESP32 motherboard.

**Record of what was done:**

- Guangyang connected keyboard matrix output to ESP32 dev board via jumper wires.
- Ran scan code to detect key presses; tested each key for row/column response.
- Found key (R4, C2) unresponsive; Zhuoer reflowed solder, issue resolved.

**Fig. 10:** Test setup diagram with ESP32 and keyboard

---

## Date: 4/26

**Objective:**  
Debug onboard DAC; fallback to external DAC.

**Record of what was done:**

- Zhuoer configured onboard PCM5102A DAC via I2S but no output observed on oscilloscope.
- Verified 3.3V DAC power and presence of I2S signals; DAC remained unresponsive.
- Connected external DAC breakout board; successful audio output achieved.
- Chose external DAC for final prototype.

**Fig. 11:** Connection of external DAC board on PCB

---

## Date: 4/27

**Objective:**  
Finalize design with mechanical packaging.

**Record of what was done:**

- Zhuoer, Henry, and Guangyang assembled keyboard and control board into 3D-printed case.
- Verified standoff fit, button clearance, and USB-C port access.
- Mounted PCBs into standoffs and secured enclosure.
- Conducted final functional test: all keys responsive, audio output functional.

**Fig. 12:** Completed assembly of digital accordion prototype

---

## References

1. Cherry MX Switch Datasheet, Cherry Corporation  
2. PCM5102A Datasheet, Texas Instruments

