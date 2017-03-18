int PIN_COLOR_R = 12;
int PIN_COLOR_G = 14;
int PIN_COLOR_B = 13;

int PIN_BUTTON = 4;
bool buttonState = false;
bool active = false;

void setup(void) {
  pinMode(PIN_COLOR_R, OUTPUT);
  pinMode(PIN_COLOR_G, OUTPUT);
  pinMode(PIN_COLOR_B, OUTPUT);

  pinMode(PIN_BUTTON, INPUT);

  // start all on
  digitalWrite(PIN_COLOR_R, HIGH);
  digitalWrite(PIN_COLOR_G, HIGH);
  digitalWrite(PIN_COLOR_B, HIGH);
}

void loop(void) {

  if (buttonState != digitalRead(PIN_BUTTON)) {
    buttonState = digitalRead(PIN_BUTTON);
    if (buttonState == true) {
      active = !active;

      if (active == true) {
        // go red if active
        digitalWrite(PIN_COLOR_R, HIGH);
        digitalWrite(PIN_COLOR_G, LOW);
        digitalWrite(PIN_COLOR_B, LOW);
      }
      else {
        // go turq if not active
        digitalWrite(PIN_COLOR_R, LOW);
        digitalWrite(PIN_COLOR_G, HIGH);
        digitalWrite(PIN_COLOR_B, HIGH);
      }

    }
  }
}

