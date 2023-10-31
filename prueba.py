import serial, time
arduino = serial.Serial('COM3', 115200)
time.sleep(2)
arduino.write(b"134")
String = arduino.readline()
print(String)
arduino.close()