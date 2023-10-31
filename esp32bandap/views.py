from django.shortcuts import render
import serial

from .forms import TransportForm

# Create your views here.
def home(request):

    if request.method == "POST":
        form = TransportForm(request.POST)

        if form.is_valid():
            
            if request.POST['initial_position'] == request.POST['final_position']:
                form = TransportForm()
                return render(request, 'home.html', {'form': form, 'error':'Posición inicial y final deben ser distintas.'})

            message = str(request.POST['initial_position'])[1]
            message += str(request.POST['final_position'])[1]
            if 'duration' in request.POST: message += request.POST['duration']

            print(message)

            # ser = serial.Serial('COM3', 9600, timeout=1)
            # ser.write(message.encode())
            
            return render(request, 'home.html', {'form': form, 'congrat':'Su solicitud fue enviada. Revise la banda.'})
            return render(request, 'results.html')

    else:
        form = TransportForm()

    return render(request, 'home.html', {'form': form})
    
