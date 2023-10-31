int s4 = 33;
int s3 = 32;
int s2 = 35;
int s1 = 34;

int der = 27;
int izq = 26;

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

  while(digitalRead(s1)==0){

    digitalWrite(der,1);

  }

  digitalWrite(der,0);


  delay(2000);
  
  while(digitalRead(s4)==0){

    digitalWrite(izq,1);

  }

  digitalWrite(izq,0);

  delay(2000);

}
