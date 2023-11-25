from django.shortcuts import render
import serial
from .forms import TransportForm
from .prueba import call
from django.http import JsonResponse

def home(request):

    if request.method == "POST":
        
        
        form = TransportForm(request.POST)

        if form.is_valid():
            
            if request.POST['initial_position'] == request.POST['final_position']:
                form = TransportForm()
                return JsonResponse({'status': 'Error', 'message': 'Posición inicial y final deben ser distintas.'})
    
            message = str(request.POST['initial_position'])[1]
            message += str(request.POST['final_position'])[1]
            if 'duration' in request.POST: 
                message += request.POST['duration']
                message = "1" + message
            else: message = "0" + message

            print('mensaje creado')

            try:
                print('antes del try')
                var = call(message)
                print('después del try')
                print(var)
                
                if var== "1":
                    print("JSON Response:", JsonResponse({'status': 'Success'}).content)
                    return JsonResponse({'status': 'Success'}, content_type='application/json')
            
    
            except serial.SerialException as e:
                print(f"Error al abrir el puerto COM: {e}")
                return JsonResponse({'status': 'Error', 'message': 'No fue posible conectarse con el puerto.'})

           
    else:
        form = TransportForm()

    return render(request, 'home.html', {'form': form})
