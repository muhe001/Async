/*
 * Melody
 *
 * Plays a melody using the Async library
 */
#include "pitches.h"
#include <Async.h>

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

const int buttonPin =  2;
bool playTune = false;

void setup() {
  // put your setup code here, to run once:

  pinMode(13, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(buttonPin), [&]() {
    playTune = true;
  }, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (playTune) {
    tune();
  }

  Async::tick();
}

void tune() {
  int totalDuration = 1;

  for (int thisNote = 0; thisNote < 8; thisNote++) {

    int noteDuration = 1000 / noteDurations[thisNote];
    int pauseBetweenNotes = noteDuration * 1.30;

    Async::setTimeout([](void* context) {
      int* note = (int*)context;
      tone(8, *note);
    },
    totalDuration, &melody[thisNote]);

     Async::setTimeout([&](void* context) {
      noTone(8);
    }, totalDuration + noteDuration);

    totalDuration = totalDuration + noteDuration + pauseBetweenNotes;
  }
  playTune = false;
}
