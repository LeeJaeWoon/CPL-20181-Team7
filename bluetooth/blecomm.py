#!/usr/bin/env python
import sys, time
import serial
from bledevice import scanble, BLEDevice

port = "/dev/ttyUSB0"
serialFromArduino = serial.Serial(port, 115200)
serialFromArduino.flushInput

def printmsg(msg):
    if msg == 'w':
        print("전진")
    elif msg == 's':
        print("후진")
    elif msg == 'a':
        print("좌회전")
    elif msg == 'd':
        print("우회전")
    elif msg == 'x':
        print("정지")

if len(sys.argv) != 2:
    print "Usage: python blecomm.py <ble address>"
    print "Scan devices are as follows:"
    print scanble(timeout=3)
    sys.exit(1)

hm10 = BLEDevice(sys.argv[1])

while True:
    input = serialFromArduino.readline()
    #mystr = raw_input("Put your command : ")
    printmsg(input)
    vh=hm10.getvaluehandle("ffe1")
    hm10.writecmd(vh, input.encode('hex'))
    data = hm10.notify()
    if data is not None:
        print "Received: ", data
