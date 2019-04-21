 #include <MIDI.h>
 #include <SoftwareSerial.h> //hard-enbled on MIDI shield
 #include <Wire.h>
 #include "Adafruit_MPR121.h" //cap sensing breakout board

//macro for bit-vector masks
 #ifndef _BV
 #define _BV(bit) (1 << (bit))
 #endif

 
 SoftwareSerial midiSerial(8,9);
    
 MIDI_CREATE_INSTANCE(SoftwareSerial, midiSerial, midiOut);

 Adafruit_MPR121 cap = Adafruit_MPR121();

 uint8_t breathPin = 3; // for pressure sensor 
 int breathPressure = 0;
 int velocity = 0;
 int ambientPressure = 0;

 int note = 0;
 uint16_t lasttouched = 0;
 uint16_t currtouched = 0;
 uint16_t hole1 = 1;
 uint16_t hole2 = 2;
 uint16_t hole3 = 4;
 uint16_t hole4 = 8;
 uint16_t hole5 = 16;
 uint16_t hole6 = 32;
 uint8_t lastnote = 62;


//helper function to bundle MIDI off on note changes, since 
//wind instruments are monophonic
//returns void, takes 2 ints, 1 uint8_t
void playNote(int noteNumber, int velocity, uint8_t lastnote) {

  // only send new message if the note has changed.
  if (noteNumber != lastnote) {
    midiOut.sendNoteOn(noteNumber, velocity, 1);
    midiOut.sendNoteOff(lastnote, velocity, 1);

  }

// end playNote  
}



void setup()
 {
     Serial.begin(9600);
     //allow time for init
     while (!Serial) {
          delay(10);
     }

     //REMOVE AFTER DEBUG
     Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  
     // Default address is 0x5A, if tied to 3.3V its 0x5B
     // If tied to SDA its 0x5C and if SCL then 0x5D
     if (!cap.begin(0x5A)) {
     Serial.println("MPR121 not found, check wiring?");
     }
     
  Serial.println("MPR121 found!");

//start MIDI service on (channel)
     midiOut.begin(1);

//calibrate pressure sensor to local condition     
     ambientPressure = analogRead(breathPin);
     for (uint8_t i = 0; i < 100; i++) {
         ambientPressure += analogRead(breathPin);
         ambientPressure = (ambientPressure / 2);
     }
     //ambientPressure is now an average of 100 samples  

//END SETUP
}


 void loop()
 {
      breathPressure = analogRead(breathPin);
       // DEBUG Serial.println(breathPressure);

      if (breathPressure > (ambientPressure + 4)) {
          currtouched = cap.touched();
      // DEBUG Serial.println(currtouched);



      if (currtouched == 63 ) {playNote(62, breathPressure, lastnote); lastnote = 62; }

      else if ( (currtouched & hole1) == 0 ) { playNote(71, breathPressure, lastnote); lastnote = 71;} 
      else if ( (currtouched & hole2) == 0 ) { playNote(69, breathPressure, lastnote); lastnote = 69;} 
      else if ( (currtouched & hole3) == 0 ) { playNote(67, breathPressure, lastnote); lastnote = 67;} 
      else if ( (currtouched & hole4) == 0 ) { playNote(66, breathPressure, lastnote); lastnote = 66;} 
      else if ( (currtouched & hole5) == 0 ) { playNote(64, breathPressure, lastnote); lastnote = 64;} 
      else if ( (currtouched & hole6) == 0 ) { playNote(74, breathPressure, lastnote); lastnote = 74;} 

         
      }

      //if breath stops, flush MIDI to avoid stuck notes
      else {
            midiOut.sendNoteOff(62, (breathPressure), 1);
            midiOut.sendNoteOff(64, (breathPressure), 1);
            midiOut.sendNoteOff(66, (breathPressure), 1);
            midiOut.sendNoteOff(67, (breathPressure), 1);
            midiOut.sendNoteOff(69, (breathPressure), 1);
            midiOut.sendNoteOff(71, (breathPressure), 1);
            midiOut.sendNoteOff(74, (breathPressure), 1);
            }
 

   
 }
