#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>
/* L9110s 모터드라이버
   오른쪽모터
   L9110s A_1A D6
   L9110s A_1B D11
   왼쪽모터
   L9110s B_1A D3
   L9110s B_1B D5
*/
int A_1A = 6;
int A_1B = 11;
int B_1A = 3;
int B_1B = 5;

/*
   초음파센서
   초음파센서 TRIG - D8
   초음파센서 ECHO - D9
*/
int trigPin = 8;
int echoPin = 9;

/*
   서보모터
   서보모터 OUT - D10
*/

/*

   HC-06 블루투스 모듈

   주의: 시리얼통신은 반드시 엇갈려 꽂혀야 합니다.

   HC-06 RX - D13

   HC-06 TX - D12

*/

int btRxPin = 12;

int btTxPin = 13;


int servoPin = 10;

Servo servo;

int speed = 200;
long duration = 0;
long leftDistance = 0;
long rightDistance = 0;

/**
   왼쪽,오른쪽 모터를 정회전하여 전진합니다.
*/

SoftwareSerial bluetoothSerial(btRxPin, btTxPin); 



void forward() {
  //모터A 정회전
  analogWrite(A_1A, speed);
  analogWrite(A_1B, 0);
  //모터B 정회전
  analogWrite(B_1A, speed);
  analogWrite(B_1B, 0);
}

/**
   왼쪽,오른쪽 모터를 역회전하여 후진합니다.
*/
void back() {
  //모터A 역회전
  analogWrite(A_1A, 0);
  analogWrite(A_1B, speed);
  //모터B 역회전
  analogWrite(B_1A, 0);
  analogWrite(B_1B, speed);
}

/**
   오른쪽 모터를 정지, 왼쪽 모터를 정회전하여 우회전합니다.
*/
void right() {
  //모터A 정회전
  analogWrite(A_1A, 0);
  analogWrite(A_1B, 0);
  //모터B 역회전
  analogWrite(B_1A, speed);
  analogWrite(B_1B, 0);
}

/**
   오른쪽 모터를 정회전, 왼쪽모터를 정지하여 좌회전합니다.
*/
void left() {
  //모터A 역회전
  analogWrite(A_1A, speed);
  analogWrite(A_1B, 0);
  //모터B 정회전
  analogWrite(B_1A, 0);
  analogWrite(B_1B, 0);
}

/**
   오른쪽,왼쪽모터를 모두 정지합니다.
*/
void stop() {
  //모터A 정지
  analogWrite(A_1A, 0);
  analogWrite(A_1B, 0);
  //모터B 정지
  analogWrite(B_1A, 0);
  analogWrite(B_1B, 0);
}



/**
   초음파센서를 이용해서 벽까지의 거리(mm)를 구합니다.
*/
float getDistanceCM() {
  digitalWrite(echoPin, LOW);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //    거리값을 저장합니다.
  float distance = pulseIn(echoPin, HIGH)  / 29.0 / 2.0;

  return distance;
}

void setup() {
  //핀을 초기화합니다.
  //L298 모터드라이버의 핀들을 출력으로 변경합니다.

  // 블루투스를 baud rate 9600으로 시작합니다.

  bluetoothSerial.begin(9600);

  //핀을 초기화합니다.

  //L298 모터드라이버의 핀들을 출력으로 변경합니다.

  pinMode(A_1A, OUTPUT);
  pinMode(A_1B, OUTPUT);
  pinMode(B_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);
  digitalWrite(A_1A, LOW);
  digitalWrite(A_1B, LOW);
  digitalWrite(B_1A, LOW);
  digitalWrite(B_1B, LOW);

  //초음파센서를 초기화합니다.
  pinMode(trigPin, OUTPUT); // Trigger is an output pin
  pinMode(echoPin, INPUT); // Echo is an input pin

  //    서보모터를 연결합니다.
  //   주의: 서보모터를 사용하게되면, 자동으로 9,10번핀의 analogWrite기능이 비활성화 됩니다.
  servo.attach(servoPin);

  //초기에 서보를 정면을 봅니다
  servo.write(90);
  delay(1000);
}

void loop() {

   /*

    'f' - 전진명령(forward)

    'b' - 후진명령(back)

    'l' - 왼쪽명령(left)

    'r' - 오른쪽명령(right)

    's' - 정지명령(stop)

  */
  if (getDistanceCM() < 3) {
    //0.5초간 정지합니다.
    stop();
    /*delay(500);
    //      서보모터를 좌회전하여 왼쪽 벽과의 거리를 변수에 저장합니다.
    servo.write(180);
    delay(500);
    //leftDistance = getDistanceCM();
    delay(500);
    //      서보를 우회전하여 오른쪽 벽과의 거리를 변수에 저장합니다.
    servo.write(0);
    delay(500);
    //rightDistance = getDistanceCM();
    delay(500);
    //      서보모터를 중앙으로 움직입니다.
    servo.write(90);
    delay(300);*/
    //       0.3초간 후진합니다.
    back();
    delay(500);
    stop();
  }
  char cmd = bluetoothSerial.read();

  switch (cmd) {

    case 'w':

      //모터A 정회전

      analogWrite(A_1A, speed);

      analogWrite(A_1B, 0);

      //모터B 정회전

      analogWrite(B_1A, speed);

      analogWrite(B_1B, 0);


      //delay(2000);
      //stop();


      break;

    case 's':

      //모터A 역회전

      analogWrite(A_1A, 0);

      analogWrite(A_1B, speed);

      //모터B 역회전

      analogWrite(B_1A, 0);

      analogWrite(B_1B, speed);

      //delay(2000);
      //stop();
      break;

    case 'd':

      //모터A 정회전

      analogWrite(A_1A, (speed/4));

      analogWrite(A_1B, 0);

      //모터B 역회전

      analogWrite(B_1A, speed);

      analogWrite(B_1B, 0);

      //delay(2000);
      //stop();
      break;

    case 'a':

      //모터A 역회전

      analogWrite(A_1A, speed);

      analogWrite(A_1B, 0);

      //모터B 정회전

      analogWrite(B_1A, (speed/4));

      analogWrite(B_1B, 0);

      //delay(2000);
      //stop();
      break;

    case 'x':

      //모터A 정지

      analogWrite(A_1A, 0);

      analogWrite(A_1B, 0);

      //모터B 정지

      analogWrite(B_1A, 0);

      analogWrite(B_1B, 0);

     delay(500);
     stop();


      break;

  }
  //20cm이내에 벽이 있다면 아래의 코드를 실행합니다.
  /*
  if (getDistanceCM() < 15) {
    //0.5초간 정지합니다.
    stop();
    delay(500);
    //      서보모터를 좌회전하여 왼쪽 벽과의 거리를 변수에 저장합니다.
    servo.write(180);
    delay(500);
    leftDistance = getDistanceCM();
    delay(500);
    //      서보를 우회전하여 오른쪽 벽과의 거리를 변수에 저장합니다.
    servo.write(0);
    delay(500);
    rightDistance = getDistanceCM();
    delay(500);
    //      서보모터를 중앙으로 움직입니다.
    servo.write(90);
    delay(1000);
    //       0.3초간 후진합니다.
    back();
    delay(500);
    stop();*/
    //      이전에 저장한 왼쪽거리가 오른쪽거리 보다 크다면 0.5초간 좌회전하며, 작다면  0.5초간 우회전합니다.
    /*if (leftDistance > rightDistance) {
      left();
    } else {
      right();
    }
    delay(500);
    //   20cm이내에 벽이 없다면 전진합니다.
  } else {
    forward();
  }*/
}
