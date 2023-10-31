from django.shortcuts import render
import serial

# Create your views here.
def home(request):

    
    
    # ser = serial.Serial('COM3', 9600, timeout=1)
    # ser.write(b"")

    return render(request, 'home.html')