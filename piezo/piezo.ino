#include <pitches.h>

byte speaker = 11, // piezoelectric sensor used as speaker at pin 11
     notecount = 7,
     i,
     note,
     duration,
     notes[]   = {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_E4, NOTE_C4}, // frequency sequency
     durations[] = {      1,       1,       1,       1,        1,      1,       3};

void setup() {
    pinMode(piezo, OUTPUT);
    for(i = 0; i < notecount; i++) {
        note = notes[i];
        duration = 1000/durations[i];
        tone(speaker, note, duration);
        delay(duration * 1.3);
        noTone(speaker);
    }
}

void loop() {
}