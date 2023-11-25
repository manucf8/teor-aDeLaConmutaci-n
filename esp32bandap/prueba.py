# # Importing Libraries 
# import serial 
# import time 
# ser = serial.Serial(port='COM3', baudrate=115200, timeout=.1)

import serial

ser = serial.Serial()
ser.baudrate = 115200
ser.port = 'COM3'
ser.setDTR(False)
ser.setRTS(False)
ser.open()


def write_read(x): 
    print('dentro de write')
    ser.write(bytes(x, 'utf-8')) 
    # time.sleep(0.05) 
    data = ser.readline() 
    return data 

def call(msg):
    num = str(msg).strip()
    value = write_read(num).decode('utf-8')
    return value