#include <ShiftRegister74HC595.h> // Register Library
#include <MIDI.h>  // Midi Library

#define LED 13 // Test LED

// create a global shift register object
ShiftRegister74HC595<2> sr(11, 12, 8); // parameters: <number of shift registers> (data pin, clock pin, latch pin)

// create midi instance
MIDI_CREATE_DEFAULT_INSTANCE();

// mapping shiftregister to note
// 8  A3
// 9  B3
// 10 C#4
// 11 D4
// 12 E4
// 13 F#4
// 14 G4 
// 15 A4
// 0 B4
// 1 C#5 
// 2 D5

// array based on mapping; lowest (A3) to highest (D5) note; 99 = placeholder
int order[] = {8,99,9,99,10,11,99,12,99,13,14,99,15,99,0,99,1,2};

 
void setup() {
  pinMode (LED, OUTPUT); // Set Arduino board pin 13 to output
  MIDI.begin(5); // Initialize the Midi Library. Listen to channel 5
  MIDI.setHandleNoteOn(HandleNoteOn); // This is important!! This command
  // tells the Midi Library which function you want to call when a NOTE ON command
  // is received. In this case it's "HandleNoteOn".
}

void loop() {
  // MIDI MODE
 MIDI.read();
  // // TEST MODE
  // for (int i = 0; i < 12; i++) {
  //   sr.set(order[i], HIGH);
  //   delay(50); 
  //   sr.set(order[i], LOW);
  //   delay(100);
  // }
  //   delay(5000);
}

void HandleNoteOn(byte channel, byte pitch, byte velocity) { 
  int offset = 57;
  int pitchint = int(pitch);

  // // TEST MODE
  // digitalWrite(LED,HIGH); 
  // delay(500);
  // digitalWrite(LED,LOW);

  // set note with delay of 50 ms
  if (pitchint > 56 && pitchint < 75) {
    sr.set(order[pitchint-offset], HIGH);
    delay(50); 
    sr.set(order[pitchint-offset], LOW);
  }

}


