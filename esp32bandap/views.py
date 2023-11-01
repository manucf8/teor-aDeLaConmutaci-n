from django.shortcuts import render
import serial
import time
from .forms import TransportForm

def write_read(x, ser): 
    ser.write(bytes(x, 'utf-8')) 
    time.sleep(0.05) 
    data = ser.readline() 
    return data 

def home(request):

    if request.method == "POST":
        
        form = TransportForm(request.POST)

        if form.is_valid():
            
            if request.POST['initial_position'] == request.POST['final_position']:
                form = TransportForm()
                return render(request, 'home.html', {'form': form, 'error':'Posición inicial y final deben ser distintas.'})
    
            try:
                ser = serial.Serial('COM3', 115200, timeout=.1)
                time.sleep(2)
                print("Conectado")

            except serial.SerialException as e:
                print(f"Error al abrir el puerto COM: {e}")
                return render(request, 'home.html', {'form': form, 'error':'No fue posible conectarse con el puerto.'})
                       

            message = str(request.POST['initial_position'])[1]
            message += str(request.POST['final_position'])[1]
            if 'duration' in request.POST: 
                message += request.POST['duration']
                message = "1" +message
            else:
                message = "0" +message
                 
            
            value = write_read(message, ser).decode('utf-8')
            print(value)

            if 'ser' in locals() and ser.is_open: ser.close()

            return render(request, 'home.html', {'form': form, 'congrat':'Su solicitud fue enviada. Revise la banda.'})

    else:
        form = TransportForm()

    return render(request, 'home.html', {'form': form})
