#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
SoftwareSerial BTserial(10, 11);

#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define DEFAULT_PULSE_WIDTH   1500
#define FREQUENCY             50

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int pwm1 = 275;
int state = 0;
int x[6] = {};
int i;
uint8_t servonum = 0;
uint8_t servonum1 = 5;
uint8_t servonum2 = 2;

uint8_t servonum9 = 9;
uint8_t servonum10 = 10;
uint8_t servonum11 = 11;

int maxvalue =170;
int minvalue = 30;
int new0;

void setup() {
  // initialize digital pin 8 as an output.

  Serial.begin(38400);
  BTserial.begin(38400);  
  pwm.begin();
  pwm.setPWMFreq(60);
  pinMode(13, OUTPUT);
  // pwm.setPWM(servonum1, 0, pulseWidth(90)); 

}
int pulseWidth(int angle)
{
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  //Serial.println(analog_value);
  return analog_value;
}

void loop() {

 if(BTserial.available() > 0) {
  int a = BTserial.read();
  x[i]=a; 
  i++;
  if(a==0){
    
    Serial.println(map(x[0],0,240,minvalue,maxvalue));
    Serial.println(map(x[1],0,240,minvalue,maxvalue));
    Serial.println(map(x[2],0,240,minvalue,maxvalue));
    Serial.println(x[3]);
    Serial.println("-------------------------------");
    i=0;
  pwm.setPWM(servonum, 0, pulseWidth(map(x[0],0,240,minvalue,maxvalue)));
  pwm.setPWM(servonum2, 0, pulseWidth(map(x[2],0,240,minvalue,maxvalue)));
  pwm.setPWM(servonum1, 0, pulseWidth(map(x[1],0,240,0,maxvalue))); 
  } 
 
  if(x[3] == 1)  // DÜZ GİTME
  {
    pwm.setPWM(servonum11, 0,pulseWidth(120));   //ileri //deneme
    pwm.setPWM(servonum10, 0, pulseWidth(60));  // ileri
  }
  if(x[3] == 2)  // GERİ GİTME
  {
    pwm.setPWM(servonum11, 0,pulseWidth(60));    //geri
    pwm.setPWM(servonum10, 0,pulseWidth(120));  //geri
  }
  if(x[3] == 3)  // SAĞA GİTME
  {
    pwm.setPWM(servonum11, 0,pulseWidth(120));   //ileri
    pwm.setPWM(servonum10, 0, pulseWidth(120)); //geri
  }
  if(x[3] == 4)  // SOLA GİTME
  {
    pwm.setPWM(servonum11, 0,pulseWidth(60));   //geri
    pwm.setPWM(servonum10, 0, pulseWidth(60)); //ileri
  }
  if(x[3] == 5)
  {
     pwm.setPWM(servonum9, 0,pulseWidth(120)); 
  }
  if(x[3] == 6)
  {
     pwm.setPWM(servonum9, 0,pulseWidth(60)); 
  }
  if(x[3] == 100)
  {
    pwm.setPWM(servonum11, 0,pulseWidth(90));   //dur
    pwm.setPWM(servonum10, 0, pulseWidth(90));  //dur
  }
  }
  }
