// PuzzleMania - lights up and plays music when puzzle is turned on and when it is completed

byte lightarray = 13, // light array at pin 13
     speaker = 12, // speaker at pin 12
     touchsensor = 11, // touch sensor at pin 11

     // top bun
     readswitch1 = 2, // touch sensor at pin 2
     // lettuce
     readswitch2 = 3, // touch sensor at pin 3
     // tomato
     readswitch3 = 4, // touch sensor at pin 4
     // burger
     readswitch4 = 5, // touch sensor at pin 5
     // bottom bun

     sequencelength = 18, // how long note sequences are, counting from 0 because of arrays
     blocklength = 1000 * 1/6, // how long each note or rest is: 1000 times a fraction of a second

     note, // currently selected note in sequence
     completed, // whether the puzzle is completed (yes if 4, no otherwise)
     done, // whether the puzzle has been completed (resets when completed = 0)

     powerjingle[] =     {392,   0, 392,   0, 392, 392, 440, 440, 440, 440, 494, 494, 523, 523, 523, 523, 523, 523}, // plays on reset
     //                   G____     G____     G____-____A____-____-____-____B____-____C____-____-____-____-____-____
     //                   0         0         0        +1                  +1        +1
     //                   G major                                                     C major

     completedjingle[] = {523, 523, 392, 392, 330, 330, 684, 684, 784, 784, 684, 684, 660, 660, 660, 660, 660, 660}, // plays on completion
     //                   C____-____G____-____E____-____F____-____G____-____F____-____E____-____-____-____-____-____
     //                   0        -3        -2        +9        +1        -1        -1
     //                   C major                       F major                       C major

     betterjingle[] =    {392, 523, 523, 523}, // plays when puzzle is further solved
     //                   G____C____-____-____
     //                   0   +3
     //                   C

     worsejingle[] =     {523, 370, 370, 370}; // plays when puzzle is
     //                   C____F#___-____-____
     //                   0   -3.5
     //                   C°

char *power = "power", *complete = "complete", *better = "better", *worse = "worse"; // strings for following function

void jingle(char *sequence) { // runs when turned on and plays sequence referred to in parameters as string argument
    note = 0; // resets note position
    for(note < sequencelength; note++;) { // until the sequence is completed, plays the note and moves to the next note
        if(sequence == power) { // if "jingle(power)" is called
            tone(speaker, powerjingle[note]); // plays note at current position
        }
        if(sequence == complete) {
            tone(speaker, completedjingle[note]);
        }
        if(sequence == better) {
            tone(speaker, betterjingle[note]);
        }
        if(sequence == worse) {
            tone(speaker, worsejingle[note]);
        }
        delay(blocklength); // note lasts for one block
    }
    noTone(speaker); // end of sequence
}

void setup() { // runs when Arduino is reset (starts from top when plugged in)
    pinMode(lightarray, OUTPUT);
    pinMode(speaker, OUTPUT);
    pinMode(readswitch1, INPUT);
    pinMode(readswitch2, INPUT);
    pinMode(readswitch3, INPUT);
    pinMode(readswitch4, INPUT);
    while(!(digitalRead(readswitch1) + digitalRead(readswitch2) + digitalRead(readswitch3) + digitalRead(readswitch4))) {
        delay(80);
    }
    digitalWrite(lightarray, HIGH); // turns on light array
    jingle(power);
    digitalWrite(lightarray, LOW); // turns off light array
}

void loop() {
    completed = digitalRead(readswitch1) + digitalRead(readswitch2) + digitalRead(readswitch3) + digitalRead(readswitch4);
    delay(80); // delay between reads for stability
    if(completed/4) { // if all pieces are together
        digitalWrite(lightarray, HIGH);
        jingle(complete);
        digitalWrite(lightarray, LOW);
        done = 1; // puzzle has been completed
    }
    if(completed > digitalRead(readswitch1) + digitalRead(readswitch2) + digitalRead(readswitch3) + digitalRead(readswitch4)) { // if the puzzle has been further completed
        digitalWrite(lightarray, HIGH);
        jingle(better);
        digitalWrite(lightarray, LOW);
    }
    if(completed < (digitalRead(readswitch1) + digitalRead(readswitch2) + digitalRead(readswitch3) + digitalRead(readswitch4))) { // if the puzzle has been taken apart before it is completed
        digitalWrite(lightarray, HIGH);
        jingle(worse);
        digitalWrite(lightarray, LOW);
    }
    else {
        digitalWrite(lightarray, LOW); // turns off light array
    }
    while(done = 1 && completed > 0) { // once completed, only reactivate when puzzle is reset
        delay(80);
    }
    if(done == 1) { // if puzzle has been completed and reset
        jingle(power);
        done = 0; // take off pause mode
    }
}