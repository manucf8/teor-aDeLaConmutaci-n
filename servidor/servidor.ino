#include "WiFi.h"

const char* ssid = "manu_miamor";
const char* password = "manu1234";
WiFiServer server(80);
int s1 = 34;
int s2 = 35;
int s3 = 32;
int s4 = 33;
int der = 26;
int izq = 27;
int A, B, delayTime;
int positions[4] = {34, 35, 32, 33};
void move(int target);


void setup() {
      
  Serial.begin(115200);

  WiFi.softAP(ssid, password);
  

  pinMode(s4, INPUT);
  pinMode(s3, INPUT);
  pinMode(s2, INPUT);
  pinMode(s1, INPUT);
  pinMode(der, OUTPUT);
  pinMode(izq, OUTPUT);

  server.begin();

}

void loop() {

  WiFiClient client = server.available();

  if (client) {

    
    String IP = client.remoteIP().toString();
    

    while (client.connected()) {

      while (!Serial.available());
      String text = Serial.readString();

      if (text[0] == '1') {

        
        A = String(text[1]).toInt();
        move(A);

        
        int B = String(text[2]).toInt();
        move(B);
      
        
        int delayTime = String(text[3]).toInt();
        delay(delayTime*1000);
        move(A);

      } else if (text[0] == '0') {

        A = String(text[1]).toInt();
        move(A);

        int B = String(text[2]).toInt();
        move(B);
        
      }

      client.println(1);
      Serial.println("1");
      delay(1000);

    }

    client.stop();
    
  }

}

void move(int target) {

  int current = 0;

  if (digitalRead(s1) == 1) {
    current = 1;
  }
  else if (digitalRead(s2) == 1) {
    current = 2;
  }
  else if (digitalRead(s3) == 1) {
    current = 3;
  }
  else if (digitalRead(s4) == 1) {
    current = 4;
  }


  int final_position = positions[target-1];

  if (current != target && current != 0) {
    if (current > target) {
      
      while (digitalRead(final_position) == 0) {
        digitalWrite(der, 1);
      }
      digitalWrite(der, 0);
    }
    else {
      while (digitalRead(final_position) == 0) {
        digitalWrite(izq, 1);
      }
      digitalWrite(izq, 0);
    }
  }
  else if (current == 0){

    while (!(digitalRead(positions[0])) && !(digitalRead(positions[1])) && !(digitalRead(positions[2])) && !(digitalRead(positions[3])) && !digitalRead(positions[4])){
      digitalWrite(der, 1);
    }
    digitalWrite(der, 0);

    move(target);
  }

}

// #define STATUS_LED_PIN 2

// int x; 
// void setup() { 
//   pinMode(STATUS_LED_PIN, OUTPUT); 
// 	Serial.begin(115200); 
// 	Serial.setTimeout(1); 
// } 

// void loop() { 

// 	while (!Serial.available());

//   String text = Serial.readString();
//   Serial.println(text);

//   if (text[0] == '1') {
//     int inicial = millis();
//     int actual = millis();
//     while ((actual - inicial) < 2000) {
//       digitalWrite(STATUS_LED_PIN, 1);
//       actual = millis();
//     }
//     digitalWrite(STATUS_LED_PIN, 0);
//   }
// }