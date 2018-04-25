#include <SoftwareSerial.h>



/* L9110s 모터드라이버

   오른쪽모터

   L9110s A_1A 6

   L9110s A_1B 11

   왼쪽모터

   L9110s B_1A 3

   L9110s B_1B 5

*/

int A_1A = 6;

int A_1B = 11;

int B_1A = 3;

int B_1B = 5;



/*

   HC-06 블루투스 모듈

   주의: 시리얼통신은 반드시 엇갈려 꽂혀야 합니다.

   HC-06 RX - D13

   HC-06 TX - D12

*/

int btRxPin = 12;

int btTxPin = 13;



/*

 * 블루투스를 사용하기 위해 소프트웨어시리얼을 실행합니다.

 * 주의 : 시리얼 통신은 반드시 엇갈려서 연결해야합니다.

 * 블루투스 RX -> 아두이노 TX

 * 블루투스 TX -> 아두이노 RX

 */

SoftwareSerial bluetoothSerial(btRxPin, btTxPin); 

int speed = 255;



void setup() {

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

}





/**

   함수내 코드가 무한히 실행됩니다.

*/

void loop() {

  /*

    'f' - 전진명령(forward)

    'b' - 후진명령(back)

    'l' - 왼쪽명령(left)

    'r' - 오른쪽명령(right)

    's' - 정지명령(stop)

  */

  char cmd = bluetoothSerial.read();

  switch (cmd) {

    case 'f':

      //모터A 정회전

      analogWrite(A_1A, speed);

      analogWrite(A_1B, 0);

      //모터B 정회전

      analogWrite(B_1A, speed);

      analogWrite(B_1B, 0);

      break;

    case 'b':

      //모터A 역회전

      analogWrite(A_1A, 0);

      analogWrite(A_1B, speed);

      //모터B 역회전

      analogWrite(B_1A, 0);

      analogWrite(B_1B, speed);

      break;

    case 'r':

      //모터A 정회전

      analogWrite(A_1A, 0);

      analogWrite(A_1B, 0);

      //모터B 역회전

      analogWrite(B_1A, speed);

      analogWrite(B_1B, 0);

      break;

    case 'l':

      //모터A 역회전

      analogWrite(A_1A, speed);

      analogWrite(A_1B, 0);

      //모터B 정회전

      analogWrite(B_1A, 0);

      analogWrite(B_1B, 0);

      break;

    case 's':

      //모터A 정지

      analogWrite(A_1A, 0);

      analogWrite(A_1B, 0);

      //모터B 정지

      analogWrite(B_1A, 0);

      analogWrite(B_1B, 0);

      break;

  }

}

