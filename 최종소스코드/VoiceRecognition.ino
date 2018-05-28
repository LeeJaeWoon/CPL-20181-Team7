#include <Servo.h>
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"
#include <Wire.h> 

VR myVR(2,3); 
SoftwareSerial btSerial(4, 5); //t,r
byte buffer[1024]; 
uint8_t records[7]; // save record
uint8_t buf[64];
int tt=0 ;
int Relay = 6;//6번 릴레이

#define zero    (0) //멈춰줘
#define one   (1)  //전진해
#define two    (2) //후진해
#define three   (3) //좌회전
#define goldRecord   (16) //우회전

void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++){
    if(buf[i]>0x19 && buf[i]<0x7F){
      Serial.write(buf[i]);
    }
    else{
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}

void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if(buf[0] == 0xFF){
    Serial.print("NONE");
  }
  else if(buf[0]&0x80){
    Serial.print("UG ");
    Serial.print(buf[0]&(~0x80), DEC);
  }
  else{
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if(buf[3]>0){
    printSignature(buf+4, buf[3]);
  }
  else{
    Serial.print("NONE");
  }
  Serial.println("\r\n");
}


void setup() { 
  btSerial.begin(9600);
  myVR.begin(9600);
  Serial.begin(115200);
  pinMode(Relay,OUTPUT); //릴레이모듈

 
  if(myVR.clear() == 0){
    Serial.println("Recognizer cleared.");
  }else{
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while(1);
  }
  if(myVR.load((uint8_t)zero) >= 0){
    Serial.println("멈춰");
  }
  
  if(myVR.load((uint8_t)one) >= 0){
    Serial.println("전진");
  }
  if(myVR.load((uint8_t)two) >= 0){
    Serial.println("후진");
  }
  if(myVR.load((uint8_t)three) >= 0){
    Serial.println("좌회전");
  }
  if(myVR.load((uint8_t)onRecord) >= 0){
    Serial.println("불켜");
  }
  if(myVR.load((uint8_t)offRecord) >= 0){
    Serial.println("불꺼");
  }
  if(myVR.load((uint8_t)goldRecord) >= 0){
    Serial.println("우회전");
  }
}

void loop() {
  int ret;
  ret = myVR.recognize(buf, 50);
  
  if(ret>0){
    switch(buf[1]){
      case zero:
        btSerial.write('0');
        Serial.println('x');
        delay(10);
        break;
      case one:
        btSerial.write('1');
        Serial.println('w');
        delay(10);
        break;
      case two:
        btSerial.write('2');
        Serial.println('s');
        delay(10);
        break;
      case three:
        btSerial.write('3');
        Serial.println('a');
        delay(10);
        break;
      case goldRecord:
        btSerial.write('4');
        Serial.println('d');
        delay(10);
        break;   
      default:
        Serial.println("Record function undefined");
        break;
    }
  }
}


