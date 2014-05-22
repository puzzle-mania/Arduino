// lights up and makes noise when puzzle is completed

byte lightarray = 13, // light array at pin 13
     completed, // whether the puzzle has been completed (yes if 4, no otherwise)

    // top bun
    touchsensor1 = 2,
    // lettuce
    touchsensor2 = 3,
    // tomato
    touchsensor3 = 4,
    // burger
    touchsensor4 = 5;
    // bottom bun

void setup() {
    pinMode(lightarray, OUTPUT);
    pinMode(touchsensor1, INPUT);
    pinMode(touchsensor2, INPUT);
    pinMode(touchsensor3, INPUT);
    pinMode(touchsensor4, INPUT);
}

void loop() {
    completed = (digitalRead(touchsensor1) + digitalRead(touchsensor2) + digitalRead(touchsensor3) + digitalRead(touchsensor4))/3;
    if(completed) {
        digitalWrite(lightarray, HIGH);
    }
    else {
        digitalWrite(lightarray, LOW);
    }
    delay(8);
}