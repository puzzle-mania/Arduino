// turns on light array when touch sensor receives input

byte lightarray = 13, // light array at pin 13
     touchsensor = 2; // touch sensor at pin 2

void setup() {
    pinMode(lightarray, OUTPUT);
    pinMode(touchsensor, INPUT);
}

void loop() {
    if(digitalRead(touchsensor)) { // if touch sensor receives input
        digitalWrite(lightarray, HIGH);
    }
    else {
        digitalWrite(lightarray, LOW);
    }
    delay(80);
}