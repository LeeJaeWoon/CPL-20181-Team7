import serial
import time
print("Start")
port = "" #블루투스 주소
bluetooth = serial.Serial(port, 9600)
print("Connected")
bluetooth.flushInput()
for i in range(5):
    print("Ping")
    bluetooth.write(b"Boop" + str.encode(str(i)))
    input_data = bluetooth.readline()
    print(input_data.decode())
    time.sleep(0.3)
bluetooth.close()