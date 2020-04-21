/*
 * Title: Microphones.ino
 * Author: Zack Pelster
 */

/*
 * Notes:
 * Testing Using Analogread():
 * Serial.print is too slow... must use either I2C or SPI!!!
 * Loop time without communication = 32 usec (Sound traveled 1.10 cm)
 * Loop time with Serial.print (2000000 Baudrate) = 340 usec (Sound traveled 11.66 cm)
 * Loop time with I2C = 44 usec (Sound traveled 1.51 cm)
 * 
 * Testing using Digitalread():
 * Loop time without communication = 16 usec (Sound traveled 5.49 mm)
 * Loop time with Serial.print (2000000 Baudrate) = 152 usec (Sound traveled 5.21 cm)
 * ---- Using Serial.print every loop will be too slow
 * ---- Solution: Only transmit data when a time difference is received
 */

#define DEBUG 0

int forward_mic = 2;  // Digital out for forward microphone
int back_mic = 3;     // Digital out for back microphone

bool triggered = false;

unsigned long trigger_time;
unsigned long max_time = 292; // Max time allowed between signals [(10 cm)/(343 m/s)=291.5 usec]
unsigned long cushion = 50000; // Cushion after being triggered

void setup() {
  Serial.begin(2000000);
  
  pinMode(forward_mic, INPUT);
  pinMode(back_mic, INPUT);

  trigger_time = micros();
  
  Serial.println("Initialization Complete");
}

void loop() {
  #if DEBUG
  unsigned long start;
  start = micros();
  #endif

  if(!triggered && !digitalRead(forward_mic) && (micros() - trigger_time) >= cushion){
    trigger_time = micros();
    triggered = true;
  }
  else if(triggered && (micros() - trigger_time) >= max_time){
    triggered = false;
  }
  else if(triggered && !digitalRead(back_mic)){
    Serial.println(micros() - trigger_time);
    triggered = false;
  }

  #if DEBUG
  Serial.println(micros() - start);
  #endif
}
