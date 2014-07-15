// PuzzleMania - lights up and plays music when puzzle is turned on and when it is completed

#include <notes.h>

byte light_array = 13, // light array at pin 13
     speaker = 12, // speaker at pin 12
     proximity_sensor = 11, // proximity sensor at pin 11

     // top bun
     read_switch_1 = 2, // touch sensor at pin 2
     // lettuce
     read_switch_2 = 3, // touch sensor at pin 3
     // tomato
     read_switch_3 = 4, // touch sensor at pin 4
     // burger
     read_switch_4 = 5, // touch sensor at pin 5
     // bottom bun

     read_switch_count = 2, // how many read switches we've received so far
     length = 0, // location in array of how long note sequences are, counting from 0 because of arrays
     BPS = 6, // note changes per second

     note, // currently selected note in sequence
     completed, // whether the puzzle is completed (yes if 4, no otherwise)
     done, // whether the puzzle has been completed (resets when completed = 0)


     power_jingle[] =     {18, // notes
                         G_4, XXX, G_4, XXX, G_4, G_4, A_4, A_4, A_4, A_4, B_4, B_4, C_5, C_5, C_5, C_5, C_5, C_5  }, // plays on reset
     //                  *____*    *____*    *____*____*____*____*____*____*____*____*____*____*____*____*____*____*
     //                  0         0         0        +1                  +1        +1
     //                  G major                                                     C major
     completed_jingle[] = {18,
                         C_5, C_5, G_4, G_4, E_4, E_4, F_5, F_5, G_5, G_5, F_5, F_5, E_5, E_5, E_5, E_5, E_5, E_5  }, // plays on completion
     //                  *____*____*____*____*____*____*____*____*____*____*____*____*____*____*____*____*____*____*
     //                  0        -3        -2        +9        +1        -1        -1
     //                  C major                       F major                       C major
     better_jingle[] =    {4,
                          G_4, C_5, C_5, C_5  }, // plays when puzzle is further solved
     //                   *____*____*____*____*
     //                   0   +3
     //                   C
     worse_jingle[] =     {4,
                          F4_, F4_, F4_, F4_  }; // plays when two pieces are taken apart
     //                   *____*____*____*____*
     //                   0
     //                   C°

char *power = "power", *complete = "complete", *better = "better", *worse = "worse"; // strings for following function

void jingle(char *sequence) { // runs when turned on and plays sequence referred to in parameters as string argument
    note = 0; // resets note position
    for(note < sequencelength; note++;) { // until the sequence is completed, plays the note and moves to the next note
        if(sequence == power && powerjingle[note] != XXX) { // if "jingle(power)" is called and the note is not a rest
            tone(speaker, powerjingle[note]); // plays note at current position
        }
        if(sequence == complete && completedjingle[note] != XXX) {
            tone(speaker, completedjingle[note]);
        }
        if(sequence == better && betterjingle[note] != XXX) {
            tone(speaker, betterjingle[note]);
        }
        if(sequence == worse && worsejingle[note] != XXX) {
            tone(speaker, worsejingle[note]);
        }
        delay(1000/BPS); // note lasts for one block
    }
    noTone(speaker); // end of sequence
}

void jingle(char *sequence) {
    note = 1;
    if(sequence == power && note < power_jingle[length] && powerjingle[note] != XXX; note++) { // when "jingle(power)" is called and the note is not a rest
        tone(speaker, power_jingle[note]);
    }
    if(sequence == power && note < power_jingle[length] && powerjingle[note] != XXX; note++) { // when "jingle(power)" is called and the note is not a rest
        tone(speaker, power_jingle[note]);
    }
    if(sequence == power && note < power_jingle[length] && powerjingle[note] != XXX; note++) { // when "jingle(power)" is called and the note is not a rest
        tone(speaker, power_jingle[note]);
    }
    if(sequence == power && note < power_jingle[length] && powerjingle[note] != XXX; note++) { // when "jingle(power)" is called and the note is not a rest
        tone(speaker, power_jingle[note]);
    }
}

void setup() { // runs when Arduino is reset (starts from top when first plugged in)
    pinMode(lightarray, OUTPUT);
    pinMode(speaker, OUTPUT);
    pinMode(readswitch1, INPUT);
    pinMode(readswitch2, INPUT);
    pinMode(readswitch3, INPUT);
    pinMode(readswitch4, INPUT);
    pinMode(touchsensor, INPUT);
    while(!digitalRead(touchsensor)) {
        delay(80);
    }
    digitalWrite(lightarray, HIGH); // turns on light array
    jingle(power);
    digitalWrite(lightarray, LOW); // turns off light array
}

void loop() {
    completion = digitalRead(readswitch1) + digitalRead(readswitch2) + digitalRead(readswitch3) + digitalRead(readswitch4);
    delay(80); // delay between reads for stability
    if(completed/readswitchcount) { // if all pieces are together
        digitalWrite(lightarray, HIGH);
        jingle(complete);
        digitalWrite(lightarray, LOW);
        done = 1; // puzzle has been completed
    }
    if(completion > digitalRead(readswitch1) + digitalRead(readswitch2) + digitalRead(readswitch3) + digitalRead(readswitch4)) { // if the puzzle has been further completed
        digitalWrite(lightarray, HIGH);
        jingle(better);
        digitalWrite(lightarray, LOW);
    }
    if(completion < (digitalRead(readswitch1) + digitalRead(readswitch2) + digitalRead(readswitch3) + digitalRead(readswitch4))) { // if the puzzle has been taken apart before it is completed
        digitalWrite(lightarray, HIGH);
        jingle(worse);
        digitalWrite(lightarray, LOW);
    }
    else {
        digitalWrite(lightarray, LOW); // turns off light array
    }
    while(done = 1 && completion > 0) { // once completed, only reactivate when puzzle is reset
        delay(80);
    }
    if(done == 1) { // if puzzle has been completed and reset
        jingle(power);
        done = 0; // take off pause mode
    }
}