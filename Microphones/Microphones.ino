/*
 * Title: Microphones.ino
 * Author: Zack Pelster
 * 
 * Based on the float64_test of ros_lib
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

#include <ros.h>
#include <std_msgs/Int32.h>

ros::NodeHandle nh;

std_msgs::Int32 time_msg;
ros::Publisher p("tdoa", &time_msg);

#define DEBUG 0
#define FASTADC 1

// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

//const int forward_mic = 2;  // Digital out for forward microphone
//const int back_mic = 3;     // Digital out for back microphone

bool triggered = false;

unsigned long trigger_time;
unsigned long max_time = 292; // Max time allowed between signals [(10 cm)/(343 m/s)=291.5 usec]
unsigned long cushion = 50000; // Cushion after being triggered

float ma_new0 = 1024, alpha0 = 0.1, ma_old0;
float ma_new1 = 1024, alpha1 = 0.1, ma_old1;

void setup()
{
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
  
//  pinMode(forward_mic, INPUT);
//  pinMode(back_mic, INPUT);

  nh.initNode();
  nh.advertise(p);

  trigger_time = micros();
}

void loop()
{
  int mic1, mic0;

  // Read values
  mic0 = analogRead(0);
  mic1 = analogRead(1);

  ma_old0 = ma_new0;
  ma_new0 = alpha0 * mic0 + (1-alpha0) * ma_old0;

  ma_old1 = ma_new1;
  ma_new1 = alpha1 * mic1 + (1-alpha1) * ma_old1;

  if(!triggered && abs(mic0 - ma_new0) >= 2.35 && (micros() - trigger_time) >= cushion){
    trigger_time = micros();
    triggered = true;
  }
  else if(triggered && (micros() - trigger_time) >= max_time){
    triggered = false;
  }
  else if(triggered && abs(mic1 - ma_new1) >= 2){
    time_msg.data = micros() - trigger_time;
    p.publish( &time_msg );
    triggered = false;
  }

  nh.spinOnce();
}
