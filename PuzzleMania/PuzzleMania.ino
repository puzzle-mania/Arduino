// PuzzleMania - lights up and plays music when puzzle is turned on and when it is completed

byte lightarray = 13, // light array at pin 13
     speaker = 12, // speaker at pin 12

     // top bun
     touchsensor1 = 2, // touch sensor at pin 2
     // lettuce
     touchsensor2 = 3, // touch sensor at pin 3
     // tomato
     touchsensor3 = 4, // touch sensor at pin 4
     // burger
     touchsensor4 = 5, // touch sensor at pin 5
     // bottom bun

     sequencelength = 18, // how long note sequences are, counting from 0 because of arrays
     blocklength = 1000/6, // how long each note block is

     note, // currently selected note in sequence
     completed, // whether the puzzle has been completed (yes if 4, no otherwise)

     powerjingle[] = {392,   0, 392,   0, 392,   0, 440, 440, 440, 440, 494, 494, 523, 523, 523, 523, 523, 523},
     //               G----     G----     G----     A----_----_----_----B----_----C----_----_----_----_----_----
     //               0         0         0        +1                  +1        +1

     completedjingle[] = {523, 523, 392, 392, 330, 330, 684, 684, 784, 784, 684, 684, 660, 660, 660, 660, 660, 660};
     //                   C----_----G----_----E----_----F----_----G----_----F----_----E----_----_----_----_----_----
     //                   0        -4        -2        +9        +1        -1        -1

void power() { // runs when turned on
    note = 0; // resets note position
    for(note < sequencelength; note++;) { // until the sequence is completed, plays the note and moves to the next note
        if(powerjingle[note] == 0) { // if the frequency value is 0
            noTone(speaker); // treats it as a rest
        }
        else {
            tone(speaker, powerjingle[note]); // plays the next note
        }
        delay(blocklength); // note lasts for one block
    }
}
void completion() { // runs when completed
    note = 0; // resets note position
    for(note < sequencelength; note++;) { // until the sequence is completed, plays the note and moves to the next note
        if(completedjingle[note] == 0) { // if the frequency value is 0
            noTone(speaker); // treats it as a rest
        }
        else {
            tone(speaker, completedjingle[note]); // plays the next note
        }
        delay(blocklength); // note lasts for one block
    }
}

void setup() {
    pinMode(lightarray, OUTPUT);
    pinMode(speaker, OUTPUT);
    pinMode(touchsensor1, INPUT);
    pinMode(touchsensor2, INPUT);
    pinMode(touchsensor3, INPUT);
    pinMode(touchsensor4, INPUT);
    power();
}

void loop() {
    completed = (digitalRead(touchsensor1) + digitalRead(touchsensor2) + digitalRead(touchsensor3) + digitalRead(touchsensor4))/3;
    if(completed) {
        digitalWrite(lightarray, HIGH);
        completion();
    }
    else {
        digitalWrite(lightarray, LOW);
    }
    delay(8);
}
