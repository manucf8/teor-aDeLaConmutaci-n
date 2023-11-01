int s1 = 34;
int s2 = 35;
int s3 = 32;
int s4 = 33;
int der = 26;
int izq = 27;

int A, B, delayTime;

#define STATUS_LED_PIN 2

int positions[4] = {34, 35, 32, 33};

void move(int target);


void setup() {

  pinMode(s4, INPUT);
  pinMode(s3, INPUT);
  pinMode(s2, INPUT);
  pinMode(s1, INPUT);
  pinMode(der, OUTPUT);
  pinMode(izq, OUTPUT);
  pinMode(STATUS_LED_PIN, OUTPUT); 

  Serial.begin(115200);
	Serial.setTimeout(1); 

}

void loop() {

  while (!Serial.available());
  String text = Serial.readString();

  if (text[0] == '1') {

    A = (String(text[1]).toInt())/100;
    move(A);

    int B = ((String(text[2]).toInt())/10) % 10;
    move(B);
  
    delay(2000);
    int delayTime = (String(text[3]).toInt()) % 10;
    delay(delayTime*1000);
    move(A);

  } else {

    A = (String(text[1]).toInt())/10;
    move(A);

    int B = (String(text[2]).toInt()) % 10;
    move(B);
    
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

  Serial.print("Current: ");
  Serial.println(current);

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

}