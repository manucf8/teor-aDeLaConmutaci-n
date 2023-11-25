int red = 27;
int green = 26;
int sound = 32;

void setup() {

  Serial.begin(115200);

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(sound, OUTPUT);

}

void loop () {

  digitalWrite(red, 1);
  delay(1000);
  digitalWrite(red, 0);
  
  for (int i = 0; i < 3; i++) {
    digitalWrite(green, 1);
    digitalWrite(sound, 1);
    delay(5);
    digitalWrite(green, 0);
    digitalWrite(sound, 0);
    delay(250);
  }

  delay(500);
  digitalWrite(green, 1);
  delay(1000);
  digitalWrite(green, 0);

}