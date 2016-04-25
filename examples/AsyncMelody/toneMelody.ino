/*
  Melody

 Plays a melody

 circuit:
 * 8-ohm speaker on digital pin 8

 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe

This example code is in the public domain.

 http://arduino.cc/en/Tutorial/Tone

 */
#include "pitches.h"
#include <StandardCplusplus.h>
#include <functional>
#include <serstream>
#include <string>
#include <vector>
#include <iterator>
//#include <pnew.cpp>  // placement new implementation


#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>

#include <Async.h>

using namespace std;
namespace std
{
  ohserialstream cout(Serial);
}

typedef void ( *EventCallback )();

struct message {
  String type;
  EventCallback callback;
  //std::function<void ()> callback;
};

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

const int buttonPin =  2;
bool playTune = false;

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

vector<string> strings;

//auto asdf;
auto add = []() { };

void listener(  )
{
    
}

void setup() {
  

  Serial.begin(9600);
  //Serial.println("setup");
  strings.push_back("Hello,");
  strings.push_back("world!");
  copy(strings.begin(),strings.end(),ostream_iterator<string>(cout," "));
  cout << endl;

  Async::setTimeout([&](void* context) {
    cout << "testing 1, 2, 3." << endl;
  }, 10000);
  
  pinMode(13, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(buttonPin), [&]() {
    playTune = true;
  }, RISING);
  Serial.println("meh");
  //tune();

  //std::function<void()> bar;// = [&]() {};
  
  message test = {
    "sadf",
    [&]() {}
  };
  //test.callback = [&]() {
  //};
}

void loop() {
  //digitalWrite(13, HIGH);
  //delay(1000);
  //digitalWrite(13, LOW);
  //delay(1000);
  
  //buttonState = digitalRead(buttonPin);
  if (playTune) {
    tune();
  }

  Async::tick();
}

void asdf() {
  Serial.println("asdf");
}

void enablePlayTune() {
  playTune = true;
}

void tune() {
  
  
  Serial.println("tune:start");
  int totalDuration = 1;

  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int note = melody[thisNote];
    Serial.print("note: ");
    Serial.println(note);
    void* noteVoid = &note;
    int* note2 = (int*)noteVoid;
    Serial.print("note2: ");
    Serial.println(*note2);
  }
  
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    
    int noteDuration = 1000 / noteDurations[thisNote];
    int pauseBetweenNotes = noteDuration * 1.30;
    unsigned int asdf = melody[thisNote];
    Serial.print("asdf: ");
    Serial.println(asdf);
    void* aa = &asdf;
    Async::setTimeout([](void* context) {
      int* ff = (int*)context;
      Serial.print("ff: ");
      Serial.println(*ff);
      tone(8, *ff);
      //return;
    },
    totalDuration, &melody[thisNote]);
    

     Async::setTimeout([&](void* context) {
      noTone(8);
    }, totalDuration + noteDuration);
    
    totalDuration = totalDuration + noteDuration + pauseBetweenNotes;
  }
  
  
  /*int steps = 500;
  int duration = 200;
  int minFrq = 2000;
  int maxFrq = 3000;
  
  for (int i = 0; i < steps; i++) {
    tone(8, maxFrq - (maxFrq - minFrq)/steps*i);
    delay(duration/steps);
  }
  noTone(8);*/
  playTune = false;
  Serial.println("tune:end");
}


