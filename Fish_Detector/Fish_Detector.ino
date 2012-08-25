#include "pitches.h"

// set pin numbers:
const int buttonPin = 0;         // the number of the pushbutton pin
const int alertLed[] = {12, 13};
const int piezo[] = {5, 6};

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

// notes in the melody:
int melody[] = {NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};

void setup() {
    // initialize the LED pins as an output:
    pinMode(alertLed[0], OUTPUT);      
    pinMode(alertLed[1], OUTPUT);      
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     
  digitalWrite(buttonPin, HIGH);    // enable the internal pullup resistor
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == LOW) {     
    digitalWrite(alertLed[0], LOW);
    digitalWrite(alertLed[1], LOW);
    playTone();
  } 
  else {
    stopAlert();
  }
}

void stopAlert() {
  digitalWrite(alertLed[0], HIGH);    // OFF
  digitalWrite(alertLed[1], HIGH);    // OFF
}

void playTone() {
   // iterate over the notes of the melody:
  int state = 0;
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(piezo[0], melody[thisNote],noteDuration);
    tone(piezo[1], melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(piezo[0]);
    noTone(piezo[1]);
  } 
}
