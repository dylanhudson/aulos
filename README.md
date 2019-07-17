# Digital Aulos
This project is the Arduino microcontroller code for a MIDI musical instrument designed as a digital replica of the Ancient Greek Aulos. 

## Hardware
The sketch has only been tested on the [Arduino UNO](https://store.arduino.cc/usa/arduino-uno-rev3) board, and requires a SparkFun [MIDI shield](https://www.sparkfun.com/products/12898) and an Adafruit [MPR121 capacitative sensing breakout board](https://www.adafruit.com/product/1982).

## Software Dependencies
The [FortySevenEffects MIDI LIbrary](https://github.com/FortySevenEffects/arduino_midi_library) and the SoftwareSerial library can be installed from within the Arduino IDE. 
The SoftwareSerial library lets us use digital pins for the serial MIDI output, keeping the hardware serial port available for the bootloader- this means we don't need to toggle the RUN/PROG switch on the MIDI shield before uploading code, and that we can still print to the console for debug purposes. 
The MIDI library allows us to send standard MIDI messages from the output port on the MIDI shield. 

## Running
After assembling the hardware, launch the Arduino IDE and upload single_bore_MIDI.ino. 

## TODO
Build [Double-bore](http://kotsanas.com/gb/exh.php?exhibit=2103002) version.




