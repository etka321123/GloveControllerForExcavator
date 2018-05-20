#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11);
//deneme sourcetree
int state = 0;
const int ledPin = 8;  //the pin your led is connected to
const int buttonPin = 2;  //the pin your button is connected to
int avg[4]={200,50,20,100};
int buttonState = 0;
unsigned long lastcom;
unsigned long lastana;
int i;
int flex1min;//flex sensorler için max ve min değerleri
int flex1max;
int flex2min;
int flex2max;
int flex3min;
int flex3max;
int value1;
int value2;
int value3;
int avgcount;
 int avgvalue1;
 int avgvalue2;
 int avgvalue3;
void setup() {
  pinMode(8 , INPUT_PULLUP);
  pinMode(2 , INPUT_PULLUP);
  pinMode(3 , INPUT_PULLUP);
  pinMode(4 , INPUT_PULLUP);
  pinMode(5 , INPUT_PULLUP);
  pinMode(6 , INPUT_PULLUP);
  pinMode(7 , INPUT_PULLUP);
  Serial.begin(9600);
  BTserial.begin(38400);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.println("kalibrasyon başlıyor");
  Serial.println("elinizi düz tutun");
  delay(2000);
  int tempvalue1;
  int tempvalue2;
  int tempvalue3;
   tempvalue1=tempvalue1 + analogRead(A0);
   tempvalue2=tempvalue2 + analogRead(A1);
   tempvalue3=tempvalue3 + analogRead(A2);
  for(int i = 0; i < 20; i++ ){
   tempvalue1=tempvalue1 + analogRead(A0);
   tempvalue2=tempvalue2 + analogRead(A1);
   tempvalue3=tempvalue3 + analogRead(A2);
   delay(10);
  }
  flex1min = tempvalue1 / 20 ;
  flex2min = tempvalue2 / 20 ;
  flex3min = tempvalue3 / 20 ;
  Serial.println(flex1min);
  Serial.println(flex2min);
  Serial.println(flex3min);
  delay(1000);
  Serial.println("elini bük");
  delay(3000);
  tempvalue1 = 0;
  tempvalue2 = 0;
  tempvalue3 = 0;
  for(int i = 0; i < 20; i++ ){
   tempvalue1=tempvalue1 + analogRead(A0);
   tempvalue2=tempvalue2 + analogRead(A1);
   tempvalue3=tempvalue3 + analogRead(A2);
   delay(10);
  }
  flex1max = tempvalue1 / 20 ;
  flex2max = tempvalue2 / 20 ;
  flex3max = tempvalue3 / 20 ;
  delay(1000);
   
  Serial.println(flex1max);
  
  Serial.println(flex2max);
  
  Serial.println(flex3max);


}

void loop() {

 
if(millis()-lastcom>20){
  if(i<5){
    BTserial.write(avg[i]);
    i++;
    lastcom=millis();
  }
  else 
  i=0;
}

if(millis()-lastana > 3){
  
  int tempvalue1=analogRead(A0);
 // Serial.println(tempvalue1);
  int tempvalue2=analogRead(A1);
  int tempvalue3=analogRead(A2);
//    Serial.println(tempvalue1);
//  Serial.println(tempvalue2);
//  Serial.println(tempvalue3);

  //if(tempvalue1 < flex1max && tempvalue1 > flex1min ){
    value1 = tempvalue1;
   // Serial.println(value1);//}
  if(tempvalue2 < flex2max && tempvalue2 > flex2min)
    value2 = tempvalue2;
  if(tempvalue3 < flex3max && tempvalue3 > flex3min)
    value3 = tempvalue3;
  if(avgcount < 10){
    avgvalue1 = avgvalue1 + value1;
    avgvalue2 = avgvalue2 + value2;
    avgvalue3 = avgvalue3 + value3;
    
    avgcount++;
   // Serial.println(avgcount);
  }

  else{
    avgcount = 0;
    avgvalue1 = avgvalue1 / 10;
    avgvalue2 = avgvalue2 / 10;
    avgvalue3 = avgvalue3 / 10;

    
//    delay(100);
  //  Serial.println("avg");
 // Serial.println(avgvalue1);
//  Serial.println(avgvalue2);
//  Serial.println(avgvalue3);
  //Serial.println("------------");

    int mapavgvalue1 = map(avgvalue1 , flex1min , flex1max , 10 , 240);
    int mapavgvalue2 = map(avgvalue2 , flex2min , flex2max , 10 , 240);
    int mapavgvalue3 = map(avgvalue3 , flex3min , flex3max , 10 , 240);
    avg[0] = mapavgvalue1;
    avg[1] = mapavgvalue2;
    avg[2] = mapavgvalue3;
    avgvalue1 = 0;
    avgvalue2 = 0;
    avgvalue3= 0;

  }
lastana = millis();

if(!digitalRead(2)) avg[3] = 100;
if(!digitalRead(3)) avg[3] = 1;
if(!digitalRead(4)) avg[3] = 2;
if(!digitalRead(5)) avg[3] = 3;
if(!digitalRead(6)) avg[3] = 4;
if(!digitalRead(7)) avg[3] = 5;
if(!digitalRead(8)) avg[3] = 6;
//if(digitalRead(7) &&digitalRead(2) &&digitalRead(3) &&digitalRead(4) &&digitalRead(5) &&digitalRead(6))  avg[3] = 100;


}//analog millis sonu
//for(int i=0; i<4;i++){
//  Serial.println(avg[i]);
//   
//  delay(10);
//}
//Serial.println("------------");
}//loop sonu



