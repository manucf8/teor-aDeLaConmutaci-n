from django.shortcuts import render
import serial
import time
from .forms import TransportForm

def home(request):

    if request.method == "POST":
        form = TransportForm(request.POST)

        if form.is_valid():
            
            if request.POST['initial_position'] == request.POST['final_position']:
                form = TransportForm()
                return render(request, 'home.html', {'form': form, 'error':'Posición inicial y final deben ser distintas.'})
    
            try:
                ser = serial.Serial('COM3', 115200)
                time.sleep(2)
                print("Conectado")

            except serial.SerialException as e:
                print(f"Error al abrir el puerto COM: {e}")
                return render(request, 'home.html', {'form': form, 'error':'No fue posible conectarse con el puerto.'})
            
            if 'initial_position' in request.POST and 'final_position' in request.POST and 'duration' in request.POST:
                ser.write(b'1')
            else:
                ser.write(b'0')
            
            A = str(request.POST['initial_position'])[1]
            if A == '1': ser.write(b'1')
            elif A == '2': ser.write(b'2')
            elif A == '3': ser.write(b'3')
            elif A == '4': ser.write(b'4')
            
            B = str(request.POST['final_position'])[1]
            if B == '1': ser.write(b'1')
            elif B == '2': ser.write(b'2')
            elif B == '3': ser.write(b'3')
            elif B == '4': ser.write(b'4')

            if 'duration' in request.POST:
                delayTime = request.POST['final_position']
                if delayTime == '0': ser.write(b'0')
                elif delayTime == '1': ser.write(b'1')
                elif delayTime == '2': ser.write(b'2')
                elif delayTime == '3': ser.write(b'3')
                elif delayTime == '4': ser.write(b'4')
                elif delayTime == '5': ser.write(b'5')
                elif delayTime == '6': ser.write(b'6')
                elif delayTime == '7': ser.write(b'7')
                elif delayTime == '8': ser.write(b'8')
                elif delayTime == '9': ser.write(b'9')

            if 'ser' in locals() and ser.is_open: ser.close()

            return render(request, 'home.html', {'form': form, 'congrat':'Su solicitud fue enviada. Revise la banda.'})

    else:
        form = TransportForm()

    return render(request, 'home.html', {'form': form})

# Importing Libraries 
import serial 
import time 
arduino = serial.Serial(port='COM3', baudrate=115200, timeout=.1) 
def write_read(x): 
    arduino.write(bytes(x, 'utf-8')) 
    time.sleep(0.05) 
    data = arduino.readline() 
    return data 

while True: 
    num = input("Enter a number: ") # Taking input from user 
    value = write_read(num).decode('utf-8')
    print(value) # printing the value 