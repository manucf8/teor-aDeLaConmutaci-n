from django.shortcuts import render
import serial
import time
from .forms import TransportForm
from .prueba import call

def write_read(x): 
    arduino = serial.Serial(port='COM3', baudrate=115200, timeout=.1) 
    arduino.write(bytes(x, 'utf-8')) 
    time.sleep(0.05) 
    data1 = arduino.readline() 

    return data1

def home(request):

    if request.method == "POST":
        
        form = TransportForm(request.POST)

        if form.is_valid():
            
            if request.POST['initial_position'] == request.POST['final_position']:
                form = TransportForm()
                return render(request, 'home.html', {'form': form, 'error':'Posición inicial y final deben arduino distintas.'})
    

            message = str(request.POST['initial_position'])[1]
            message += str(request.POST['final_position'])[1]
            if 'duration' in request.POST: 
                message += request.POST['duration']
                message = "1" +message
            else:
                message = "0" +message
            
            try:
                call(message)
    
            except serial.SerialException as e:
                print(f"Error al abrir el puerto COM: {e}")
                return render(request, 'home.html', {'form': form, 'error':'No fue posible conectarse con el puerto.'})
                       


            return render(request, 'home.html', {'form': form, 'congrat':'Su solicitud fue enviada. Revise la banda.'})

    else:
        form = TransportForm()

    return render(request, 'home.html', {'form': form})
