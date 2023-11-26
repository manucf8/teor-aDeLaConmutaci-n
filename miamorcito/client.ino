#include <WiFi.h>

int red = 27;
int green = 26;
int sound_power = 32;

//Definir credenciales para conexión wifi
const char* ssid = "manu_miamor";
const char* password = "manu1234";

void setup() {

  //Iniciar comunicación
  Serial.begin(115200);
  
  // Usar credenciales para conexión wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando...");
  }
  Serial.println("Conectado");

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(sound_power, OUTPUT);
  delay(1000);

}

void loop() {

  delay(1000);

  WiFiClient client;
  if (!client.connect(WiFi.gatewayIP(), 80)) {
    Serial.println("Conexión fallida");
    return;
  }

  while (client.connected()) {

    

    //Leer hasta que reciba información que le indique que ya finalizó el recorrido
    String line = client.readStringUntil('\n');

    //Encender led rojo mientras se recibe solicitud y/o se completa el recorrido
    digitalWrite(red, 1);


    //Mientras el recorrido no haya finalizado, seguir leyendo y no hacer nada más
    while (line.length() == 0) {
      line = client.readStringUntil('\n');
      
    }

    //Apagar led rojo y titilar led verde y bocina 3 veces
    digitalWrite(red, 0);

    digitalWrite(green, 1);
    digitalWrite(sound_power, 1);
    delay(80);
    digitalWrite(green, 0);
    digitalWrite(sound_power, 0);
    delay(200);
    digitalWrite(green, 1);
    digitalWrite(sound_power, 1);
    delay(80);
    digitalWrite(green, 0);
    digitalWrite(sound_power, 0);
    delay(200);
    digitalWrite(green, 1);
    digitalWrite(sound_power, 1);
    delay(80);
    digitalWrite(green, 0);
    digitalWrite(sound_power, 0);
    delay(200);
    digitalWrite(green, 1);
    delay(3000);

    digitalWrite(green, 0);

  }
  
  client.stop();
}
