from music21 import converter, chord, note
import sys

OCTAVE = 4  # match your Arduino getNote()

def midi_note_to_key(midi_note, octave=OCTAVE):
    return midi_note - ((octave + 1) * 12)

def extract_chords_with_timing(midi_path):
    score = converter.parse(midi_path)
    flat = score.chordify().flat.notes.stream()
    tempo = score.metronomeMarkBoundaries()[0][2]

    chord_events = []
    last_offset = 0

    for el in flat:
        current_offset = el.offset

        # Insert a rest if there's a gap between events
        gap = current_offset - last_offset
        if gap > 0:
            rest_duration_ms = int(tempo.secondsPerQuarter() * gap * 1000)
            chord_events.append(([], 0, rest_duration_ms))  # Rest

        # Get notes as keys
        if isinstance(el, chord.Chord):
            keys = sorted(set(midi_note_to_key(p.midi) for p in el.pitches))
        elif isinstance(el, note.Note):
            keys = [midi_note_to_key(el.pitch.midi)]
        else:
            continue

        duration_beats = el.duration.quarterLength
        duration_ms = int(tempo.secondsPerQuarter() * duration_beats * 1000)
        chord_events.append((keys, len(keys), duration_ms))

        last_offset = current_offset + el.duration.quarterLength

    return chord_events

def print_arduino_code(chords):
    print("ChordEvent chordProgression[] = {")
    for keys, count, duration in chords:
        if count == 0:
            print(f"  {{{{{key_str}}}, {0}, {duration}}},  // rest")
        else:
            key_str = ", ".join(str(k) for k in keys)
            print(f"  {{{{{key_str}}}, {count}, {duration}}},")
    print("};")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python midi.py <file.mid>")
        sys.exit(1)

    midi_path = f"./music/{sys.argv[1]}"
    chords = extract_chords_with_timing(midi_path)
    print_arduino_code(chords)
