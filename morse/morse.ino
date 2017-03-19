int PIN_COLOR_R = 12;
int PIN_COLOR_G = 14;
int PIN_COLOR_B = 13;

int PIN_BUTTON = 4;
bool buttonState = false;
bool active = false;

int dialRead = 0;
int PIN_DIAL = A0;

int PIN_BUZZER = 5;

void setup(void) {
  pinMode(PIN_COLOR_R, OUTPUT);
  pinMode(PIN_COLOR_G, OUTPUT);
  pinMode(PIN_COLOR_B, OUTPUT);

  pinMode(PIN_BUTTON, INPUT);

  pinMode(PIN_DIAL, INPUT);

  pinMode(PIN_BUZZER, OUTPUT);
}

void loop(void) {

  digitalWrite(PIN_BUZZER, HIGH);
  delay(4);
  digitalWrite(PIN_BUZZER, LOW);
  delay(4);

  // between 11 and 908
  dialRead = analogRead(PIN_DIAL);

  if (buttonState != digitalRead(PIN_BUTTON)) {
    buttonState = digitalRead(PIN_BUTTON);
    if (buttonState == true) {
      active = !active;
    }
  }

  if (active == true) {
    if (dialRead < 130) {
      digitalWrite(PIN_COLOR_R, LOW);
      digitalWrite(PIN_COLOR_G, HIGH);
      digitalWrite(PIN_COLOR_B, LOW);
    }
    else if (dialRead < 260) {
      digitalWrite(PIN_COLOR_R, LOW);
      digitalWrite(PIN_COLOR_G, LOW);
      digitalWrite(PIN_COLOR_B, HIGH);
    }
    else if (dialRead < 390) {
      digitalWrite(PIN_COLOR_R, HIGH);
      digitalWrite(PIN_COLOR_G, LOW);
      digitalWrite(PIN_COLOR_B, LOW);
    }
    else if (dialRead < 520) {
      digitalWrite(PIN_COLOR_R, LOW);
      digitalWrite(PIN_COLOR_G, HIGH);
      digitalWrite(PIN_COLOR_B, HIGH);
    }
    else if (dialRead < 650) {
      digitalWrite(PIN_COLOR_R, HIGH);
      digitalWrite(PIN_COLOR_G, HIGH);
      digitalWrite(PIN_COLOR_B, LOW);
    }
    else if (dialRead < 780) {
      digitalWrite(PIN_COLOR_R, HIGH);
      digitalWrite(PIN_COLOR_G, LOW);
      digitalWrite(PIN_COLOR_B, HIGH);
    }
    else {
      digitalWrite(PIN_COLOR_R, HIGH);
      digitalWrite(PIN_COLOR_G, HIGH);
      digitalWrite(PIN_COLOR_B, HIGH);
    }
  }
  else {
    digitalWrite(PIN_COLOR_R, LOW);
    digitalWrite(PIN_COLOR_G, LOW);
    digitalWrite(PIN_COLOR_B, LOW);
  }
}

