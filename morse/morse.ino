int PIN_COLOR_R = 12;
int PIN_COLOR_G = 14;
int PIN_COLOR_B = 13;

void setup(void) {
  pinMode(PIN_COLOR_R, OUTPUT);
  pinMode(PIN_COLOR_G, OUTPUT);
  pinMode(PIN_COLOR_B, OUTPUT);
}

void loop(void) {
  digitalWrite(PIN_COLOR_R, HIGH);
  digitalWrite(PIN_COLOR_G, HIGH);
  digitalWrite(PIN_COLOR_B, HIGH);
  delay(1000);
  digitalWrite(PIN_COLOR_R, HIGH);
  digitalWrite(PIN_COLOR_G, LOW);
  digitalWrite(PIN_COLOR_B, LOW);
  delay(1000);
  digitalWrite(PIN_COLOR_R, LOW);
  digitalWrite(PIN_COLOR_G, LOW);
  digitalWrite(PIN_COLOR_B, HIGH);
  delay(1000);
  digitalWrite(PIN_COLOR_R, LOW);
  digitalWrite(PIN_COLOR_G, HIGH);
  digitalWrite(PIN_COLOR_B, LOW);
  delay(1000);
}

