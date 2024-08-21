#ifndef CHORD_H
#define CHORD_H

#include <Arduino.h>
#include <Sound.h>
#include <Note.h>
#include <vector>

class Chord : public Sound {
public:
    Chord(char id, String name, std::vector<Note*> notes);

    const std::vector<Note*>& getNotes() const { return notes; }

    // Predefined chords: Major Chords
    static Chord C;
    static Chord Db;
    static Chord D;
    static Chord Eb;
    static Chord E;
    static Chord F;
    static Chord Gb;
    static Chord G;
    static Chord Ab;
    static Chord A;
    static Chord Bb;
    static Chord B;

    // Minor Chords
    static Chord Cm;
    static Chord Dbm;
    static Chord Dm;
    static Chord Ebm;
    static Chord Em;
    static Chord Fm;
    static Chord Gbm;
    static Chord Gm;
    static Chord Abm;
    static Chord Am;
    static Chord Bbm;
    static Chord Bm;

    // Dominant 7th Chords
    static Chord C7;
    static Chord Db7;
    static Chord D7;
    static Chord Eb7;
    static Chord E7;
    static Chord F7;
    static Chord Gb7;
    static Chord G7;
    static Chord Ab7;
    static Chord A7;
    static Chord Bb7;
    static Chord B7;

    // Diminished 7th Chords
    static Chord Cdim;
    static Chord Dbdim;
    static Chord Ddim;
    static Chord Ebdim;
    static Chord Edim;
    static Chord Fdim;
    static Chord Gbdim;
    static Chord Gdim;
    static Chord Abdim;
    static Chord Adim;
    static Chord Bbdim;
    static Chord Bdim;

private:
    std::vector<Note*> notes;
};

#endif // CHORD_H
