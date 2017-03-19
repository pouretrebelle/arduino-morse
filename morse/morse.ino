int PIN_COLOR_R = 12;
int PIN_COLOR_G = 14;
int PIN_COLOR_B = 13;

int PIN_BUTTON = 4;
bool buttonState = false;
bool buttonActive = false;

int dialRead = 0;
int PIN_DIAL = A0;

int PIN_BUZZER = 5;
int buzzSpeed = 20;

const char* message = "SOS";

void setup(void) {
  pinMode(PIN_COLOR_R, OUTPUT);
  pinMode(PIN_COLOR_G, OUTPUT);
  pinMode(PIN_COLOR_B, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_DIAL, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
}

void loop(void) {
  if (message) {
    outputString(morseEncode(message));
    message = "";
  }

  // between 11 and 908
  dialRead = analogRead(PIN_DIAL);

  if (buttonState != digitalRead(PIN_BUTTON)) {
    buttonState = digitalRead(PIN_BUTTON);
    if (buttonState == true) {
      buttonActive = !buttonActive;
    }
  }
}

void buzz(int length, bool active) {
  int loops = buzzSpeed * length;

  if (active) {
    for (int i = 0; i < loops; i++) {
      // 3 is enough for an okay square wave
      digitalWrite(PIN_BUZZER, HIGH);
      delay(3);
      digitalWrite(PIN_BUZZER, LOW);
      delay(3);
    }
  }
  else {
    // if we don't want it buzzing just delay
    delay(loops*6);
  }
}

void outputString(String morseMessage) {
  for(int i = 0; i <= morseMessage.length(); i++) {
    switch(morseMessage[i]) {
      case '.': // dit
        buzz(1, true);
        buzz(1, false);
        break;

      case '-': // dah
        buzz(3, true);
        buzz(1, false);
        break;

      case ' ': // gap
        buzz(1, false);
    }
  }
}

