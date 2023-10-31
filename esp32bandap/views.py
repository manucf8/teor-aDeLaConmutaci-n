from django.shortcuts import render
import serial

from .forms import TransportForm

# Create your views here.
def home(request):

    # if this is a POST request we need to process the form data
    if request.method == "POST":
        # create a form instance and populate it with data from the request:
        form = TransportForm(request.POST)
        # check whether it's valid:
        if form.is_valid():
            # process the data in form.cleaned_data as required
            # ...
            # redirect to a new URL:
            return render(request, 'results.html')

    # if a GET (or any other method) we'll create a blank form
    else:
        form = TransportForm()

    return render(request, 'home.html', {'form': form})
    
    # ser = serial.Serial('COM3', 9600, timeout=1)
    # ser.write(b"")
