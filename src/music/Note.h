#ifndef NOTE_H
#define NOTE_H

#include <Arduino.h>
#include <Sound.h>

class Note : public Sound {
public:
    enum Accidental {
        FLAT,
        SHARP,
        NONE
    };

    int getOctave() const { return octave; }
    Accidental getAccidental() const { return accidental; }
    float getFrequency() const { return frequency; }

    // Standard notes on a full 88-key piano keyboard, spanning from A0 to C8.
    static Note A_0;
    static Note Bb_0;
    static Note B_0;
    static Note C_1;
    static Note Db_1;
    static Note D_1;
    static Note Eb_1;
    static Note E_1;
    static Note F_1;
    static Note Gb_1;
    static Note G_1;
    static Note Ab_1;
    static Note A_1;
    static Note Bb_1;
    static Note B_1;
    static Note C_2;
    static Note Db_2;
    static Note D_2;
    static Note Eb_2;
    static Note E_2;
    static Note F_2;
    static Note Gb_2;
    static Note G_2;
    static Note Ab_2;
    static Note A_2;
    static Note Bb_2;
    static Note B_2;
    static Note C_3;
    static Note Db_3;
    static Note D_3;
    static Note Eb_3;
    static Note E_3;
    static Note F_3;
    static Note Gb_3;
    static Note G_3;
    static Note Ab_3;
    static Note A_3;
    static Note Bb_3;
    static Note B_3;
    static Note C_4;
    static Note Db_4;
    static Note D_4;
    static Note Eb_4;
    static Note E_4;
    static Note F_4;
    static Note Gb_4;
    static Note G_4;
    static Note Ab_4;
    static Note A_4;
    static Note Bb_4;
    static Note B_4;
    static Note C_5;
    static Note Db_5;
    static Note D_5;
    static Note Eb_5;
    static Note E_5;
    static Note F_5;
    static Note Gb_5;
    static Note G_5;
    static Note Ab_5;
    static Note A_5;
    static Note Bb_5;
    static Note B_5;
    static Note C_6;
    static Note Db_6;
    static Note D_6;
    static Note Eb_6;
    static Note E_6;
    static Note F_6;
    static Note Gb_6;
    static Note G_6;
    static Note Ab_6;
    static Note A_6;
    static Note Bb_6;
    static Note B_6;
    static Note C_7;
    static Note Db_7;
    static Note D_7;
    static Note Eb_7;
    static Note E_7;
    static Note F_7;
    static Note Gb_7;
    static Note G_7;
    static Note Ab_7;
    static Note A_7;
    static Note Bb_7;
    static Note B_7;
    static Note C_8;

private:
    Note(char id, String name, int octave, Accidental accidental, float frequency);

    int octave;            // E.g., 4 for middle C
    Accidental accidental; // FLAT, SHARP, or NONE
    float frequency;       // Frequency in Hz
};

#endif // NOTE_H
