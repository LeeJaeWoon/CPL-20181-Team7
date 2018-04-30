#include "SoftwareSerial.h"

SoftwareSerial serial_connection(10,11);

#define BUFFER_SIZE 64

char inData[BUFFER_SIZE];
char inChar = -1;
int cnt = 0;
int i = 0;

void setup()
{
  Serial.begin(9600);
  serial_connection.begin(9600);
  serial_connection.println("Ready");
  Serial.println("Started");
}

void loop()
{
  byte byte_cnt = serial_connection.available();

  if(byte_cnt)
  {
    Serial.println("Incoming Data");
    int first_bytes = byte_cnt;
    int remain_bytes = 0;

    if(first_bytes >= BUFFER_SIZE-1)
    {
      remain_bytes = byte_cnt-(BUFFER_SIZE-1);
    }

    for(i=0;i<first_bytes;i++)
    {
      inChar = serial_connection.read();
      inData[i] = inChar;
    }

    inData[i] = '\0';

    for(i=0;i<remain_bytes;i++)
    {
      inChar = serial_connection.read();
    }

    Serial.println(inData);
    serial_connection.println("Hello from Blue" + String(cnt));
    cnt++;
  }
  delay(300);
}
