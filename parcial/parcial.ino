int s1 = 34;
int s2 = 35;
int s3 = 32;
int s4 = 33;
int der = 27;
int izq = 26;

int A, B, delayTime, option;


void move(int target);


void setup() {

  pinMode(s4, INPUT);
  pinMode(s3, INPUT);
  pinMode(s2, INPUT);
  pinMode(s1, INPUT);
  pinMode(der, OUTPUT);
  pinMode(izq, OUTPUT);

  Serial.begin(115200);

}

void loop() {

  if (Serial.available() > 0) {
    
    option = Serial.read();

    if (option > 119) {

      A = option/100;
      move(A);
      delay(2000);

      B = (option/10) % 10;
      move(B);
      
      delayTime = option % 10;
      delay(delayTime);
      move(A);

    }

    else {

      A = option/10;
      move(A);
      delay(2000);
      B = option % 10;
      move(B);

    }

    
  }

}

void move(target) {

  int current = 0;
  if (digitalRead(s1) == 1) current = 1;
  if (digitalRead(s2) == 1) current = 2;
  if (digitalRead(s3) == 1) current = 3;
  if (digitalRead(s4) == 1) current = 4;

  if (current != target) {
    if (current > target) {
      while (digitalRead(target) != 1) digitalWrite(der, 1);
    }
    else {
      while (digitalRead(target) != 1) digitalWrite(izq, 1);
    }
  }

}