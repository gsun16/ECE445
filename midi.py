from mido import MidiFile
from collections import defaultdict
import sys
OCTAVE = 4  # default octave for MIDI notes

def midi_to_chords(midi_path, time_window=0.1, base_octave=4):
    mid = MidiFile(midi_path)
    ticks_per_beat = mid.ticks_per_beat
    tempo = 500000  # default microseconds per beat (120 bpm)

    # Convert ticks to time (seconds)
    def ticks_to_seconds(ticks):
        return mido.tick2second(ticks, ticks_per_beat, tempo)

    # Accumulate note on events in time-sorted order
    current_time = 0
    chords = []
    current_chord = []
    last_time = 0

    for msg in mid:        
        if msg.type == 'set_tempo':
            tempo = msg.tempo
        current_time += msg.time

        if msg.type == 'note_on' and msg.velocity > 0:
            note = msg.note
            time_since_last = current_time - last_time
            if time_since_last > time_window:
                if current_chord:
                    chords.append((last_time, current_chord))
                current_chord = [note]
                last_time = current_time
            else:
                current_chord.append(note)

    if current_chord:
        chords.append((last_time, current_chord))

    return chords

def midi_note_to_key(midi_note, octave_offset=OCTAVE):
    return midi_note - ((octave_offset + 1) * 12)

def export_as_arduino_chord_events(chords, octave=4, default_duration=250):
    print("ChordEvent chordProgression[] = {")
    for _, notes in chords:
        keys = [midi_note_to_key(n, octave) for n in notes]
        keys_str = ", ".join(str(k) for k in keys)
        print(f"  {{{{{keys_str}}}, {len(keys)}, {default_duration}}},")
    print("};")

if __name__ == "__main__":
    import mido
    if len(sys.argv) < 2:
        print("Usage: python midi_to_chords.py <file.mid>")
        sys.exit(1)

    midi_path = sys.argv[1]
    chords = midi_to_chords(midi_path)
    OCTAVE = 4  # match your Arduino setting
    export_as_arduino_chord_events(chords, octave=OCTAVE)
