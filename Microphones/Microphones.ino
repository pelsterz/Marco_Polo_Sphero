/*
 * Title: Microphones.ino
 * Author: Zack Pelster
 * 
 * Microphone program that increases the speed of the Arduino's ADC
 * to be able to keep up with the speed of sound!
 * Based on jmknapp example: https://forum.arduino.cc/index.php?topic=6549.0
 */

#include <Wire.h>

#define SLAVE_ADDRESS 0x04

#define DEBUG 1
#define FASTADC 1

// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

uint8_t bytes[2];

void setup() {
 
#if FASTADC
  /*
   * ADPS2 | ADPS1 | ADPS0 | Factor | Time (msec)
   * 0     | 0     | 0     | 2      | -
   * 0     | 0     | 1     | 2      | -
   * 0     | 1     | 0     | 4      | -
   * 0     | 1     | 1     | 8      | 8
   * 1     | 0     | 0     | 16     | 16
   */
  // set prescale
  sbi(ADCSRA,ADPS2);
  cbi(ADCSRA,ADPS1);
  cbi(ADCSRA,ADPS0);
#endif
  
  Serial.begin(9600);
  
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  
  // initialize i2c
  Wire.begin();

  // define callbacks for i2c communication
  Wire.onRequest(sendData);
  
  Serial.println("Initialization Complete");
}

void loop() {
  #if DEBUG
  unsigned long start;
  start = micros();
  #endif

  digitalRead(2);
  digitalRead(3);

  #if DEBUG
  Serial.println(micros() - start);
  #endif
}

// callback for sending data
void sendData(){
  int mic1, mic0;
  
  #if DEBUG
  unsigned long start;
  start = micros();
  #endif
  
  // Serial.print is too slow... must use either I2C or SPI!!!
  // Loop time without communication = 32 usec (Sound traveled 1.10 cm)
  // Loop time with Serial.print (2000000 Baudrate) = 340 usec (Sound traveled 11.66 cm)
  // Loop time with I2C = 44 usec (Sound traveled 1.51 cm)
  
  // Read values
  mic0 = analogRead(0);
  mic1 = analogRead(1);

  // Send mic0
  bytes[0] = mic0;
  bytes[1] = mic0 >> 8;
  Wire.write(bytes, 2);

  // Send mic1
  bytes[0] = mic1;
  bytes[1] = mic1 >> 8;
  Wire.write(bytes, 2);

  #if DEBUG
  Serial.println(micros() - start);
  
  Serial.print(mic0);
  Serial.print(" ");
  Serial.println(mic1);
  #endif
}
