#include <QList.h>
#include "QList.cpp"

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

QList<char*> incoming;
bool messagesPending = false;

void setup(void) {
  incoming.push_back("SOS");
  messagesPending = true;

  pinMode(PIN_COLOR_R, OUTPUT);
  pinMode(PIN_COLOR_G, OUTPUT);
  pinMode(PIN_COLOR_B, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_DIAL, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
}

void loop(void) {
  checkStates();

  if (messagesPending) {
    // set to red
    digitalWrite(PIN_COLOR_R, HIGH);
    digitalWrite(PIN_COLOR_G, LOW);
    digitalWrite(PIN_COLOR_B, LOW);
  }
  else {
    // set to green
    digitalWrite(PIN_COLOR_R, LOW);
    digitalWrite(PIN_COLOR_G, HIGH);
    digitalWrite(PIN_COLOR_B, LOW);
  }

  if (buttonActive) {
    // set to blue
    digitalWrite(PIN_COLOR_R, LOW);
    digitalWrite(PIN_COLOR_G, LOW);
    digitalWrite(PIN_COLOR_B, HIGH);

    // wait a little after button activation
    delay(500);
    while (incoming.size() > 0) {
      outputString(morseEncode(incoming.front()));
      incoming.pop_front();
      // leave a space between messages
      buzz(10, false);
    }
    messagesPending = false;
    buttonActive = false;
  }

}

void checkStates(void) {
  // we need to remove this from the loop
  // so it can happen every time the buzzer sounds
  // because otherwise it'll be blocked by the delays

  // between 11 and 908
  dialRead = analogRead(PIN_DIAL);
  buzzSpeed = round(map(dialRead, 11, 908, 30, 3));

  if (buttonState != digitalRead(PIN_BUTTON)) {
    buttonState = digitalRead(PIN_BUTTON);
    if (buttonState == true) {
      buttonActive = !buttonActive;
    }
  }
}

void buzz(int length, bool active) {
  checkStates();

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

