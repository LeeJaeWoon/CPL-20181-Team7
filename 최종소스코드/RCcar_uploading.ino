#include <SoftwareSerial.h> //블루투스를 사용하기위한 라이브러리

SoftwareSerial bSerial(2, 3); //블루투스 모듈을 연결하는 핀 지정(아날로그 핀도 사용 가능), TX에 12, RX에 13을 연결

const int motorLeftF = 4; // 왼쪽 모터의 전진 신호는 11번으로 정의
const int motorLeftB = 5; // 왼쪽 모터의 후진 신호는 10번으로 정의
const int motorRightF = 6; // 오른쪽 모터의 전진 신호는 6번으로 정의
const int motorRightB = 7; // 오른쪽 모터의 후진 신호는 9번으로 정의

boolean direction = true;

void setup() {
  bSerial.begin(9600);  // 블루투스 통신을 하기 위해 Serial 통신 속도를 9600bps로 설정
  pinMode(motorRightF, OUTPUT);
  pinMode(motorRightB, OUTPUT);
  pinMode(motorLeftF, OUTPUT);
  pinMode(motorLeftB, OUTPUT);
  // 모터 2개를 제어하기 위해 모터드라이버와 연결된 핀을 출력으로 설정
}


void loop() { 
  char readed;
  while(bSerial.available()){
    readed=bSerial.read();
    setDirection(readed); // 입력받은 문자에 맞는 동작을 실행
  }
}


void left(int d){ //왼쪽 모터 제어 
  if(d == 1){
    digitalWrite(motorLeftB, LOW);
    digitalWrite(motorLeftF, HIGH);
  } 
  else if(d == 0){ 
    digitalWrite(motorLeftB, LOW);
    digitalWrite(motorLeftF, LOW);     
  }
  else {
    digitalWrite(motorLeftB, HIGH);
    digitalWrite(motorLeftF, LOW); 
  }
}

void right(int d){ //오른쪽 모터 제어 
  if(d == 1){
    digitalWrite(motorRightB, LOW);
    digitalWrite(motorRightF, HIGH);
  } 
  else if(d == 0){
    digitalWrite(motorRightB, LOW);
    digitalWrite(motorRightF, LOW);     
  }
  else {
    digitalWrite(motorRightB, HIGH);
    digitalWrite(motorRightF, LOW);
  } 
}

void setDirection(unsigned char d){
  switch(d){
  case 'w': // f를 직진으로 정의
    left(1);   
    right(1);
    break;
  case 's': // b를 후진으로 정의
    left(-1);   
    right(-1); 
    break;
  case 'a': // l을 좌회전으로 정의
    left(0);  //왼쪽 바퀴 정지
    right(1); //오른쪽 바퀴 회전
    break;
  case 'd': // r을 우회전으로 정의
    left(1);   
    right(0);
    break;
  
  case 'x': //s를 정지로 정의
    left(0);
    right(0);
  default :
    break;
  }
}
