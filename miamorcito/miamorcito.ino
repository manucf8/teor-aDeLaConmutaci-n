#include <WiFi.h>

int red = 27;
int green = 26;
int sound_power = 32;

const char* ssid = "manu_miamor";
const char* password = "manu1234";

void setup() {

  Serial.begin(115200);

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

    Serial.println("entró");
    String line = client.readStringUntil('\n');

    digitalWrite(red, 1);
    
    while (line.length() == 0) {
      line = client.readStringUntil('\n');
      
    }

    Serial.println("fuera del while, ya recibió instrucción");
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
  Serial.println("salió");
  client.stop();
}