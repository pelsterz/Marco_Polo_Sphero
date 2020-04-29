/*
 * Title: Pin_Tones.ino
 * Modified by: Zack Pelster (4/28/2020)
 */

/*
  Multiple tone player

  Plays multiple tones on multiple pins in sequence

  circuit:
  - three 8 ohm speakers on digital pins 6, 7, and 8

  created 8 Mar 2010
  by Tom Igoe
  based on a snippet from Greg Borenstein

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone4
*/

void setup() {
  
}

void loop() {
  // play a note on pin 8 for 500 ms:
  tone(8, 523, 50);
  delay(1000);
  // turn off tone function for pin 8:
  noTone(8);
}
