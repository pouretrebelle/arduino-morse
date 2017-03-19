#include <QList.h>
#include "QList.cpp"

int PIN_COLOR_R = 12;
int PIN_COLOR_B = 13;

int PIN_BUTTON = 16;
bool buttonState = false;
bool buttonActive = false;

int dialRead = 0;
int PIN_DIAL = A0;

int PIN_PIEZO = 15;
int PIN_MAGNET = 14;
int PIN_OUTPUT;
int PIN_TOGGLE_PIEZO = 4;
int PIN_TOGGLE_MAGNET = 5;
bool piezoActive = false;
bool magnetActive = false;
bool outputActive = false;
int buzzSpeed = 20;

QList<char*> incoming;
bool messagesPending = false;

void setup(void) {
  incoming.push_back("SOS");
  messagesPending = true;

  pinMode(PIN_COLOR_R, OUTPUT);
  pinMode(PIN_COLOR_B, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_DIAL, INPUT);
  pinMode(PIN_MAGNET, OUTPUT);
  pinMode(PIN_PIEZO, OUTPUT);
  pinMode(PIN_TOGGLE_MAGNET, INPUT);
  pinMode(PIN_TOGGLE_PIEZO, INPUT);
}

void loop(void) {
  checkStates();

  if (!outputActive) {
    return;
  }

  if (messagesPending) {
    // set to red
    digitalWrite(PIN_COLOR_R, HIGH);
    digitalWrite(PIN_COLOR_B, LOW);
  }
  else {
    // set to blue
    digitalWrite(PIN_COLOR_R, LOW);
    digitalWrite(PIN_COLOR_B, HIGH);
  }

  if (buttonActive) {
    // set to pink
    digitalWrite(PIN_COLOR_R, HIGH);
    digitalWrite(PIN_COLOR_B, HIGH);

    // wait a little after button activation
    delay(200);

    // loop through incoming, only if output is active
    while (incoming.size() > 0 && outputActive) {
      outputString(morseEncode(incoming.front()));

      if (outputActive) {
        // only remove message if the output is still active
        incoming.pop_front();
      }

      // leave a space between messages
      if (incoming.size() > 0) {
        buzz(10, false);
      }
    }

    // if output is inactive there will still be messages pending
    // because they won't have been poped
    if (outputActive) {
      messagesPending = false;
    }

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

  // check the toggle switch status
  piezoActive = digitalRead(PIN_TOGGLE_PIEZO);
  magnetActive = digitalRead(PIN_TOGGLE_MAGNET);
  bool outputActiveNext;
  if (!piezoActive && !magnetActive) {
    outputActiveNext = false;
  }
  else {
    outputActiveNext = true;
  }

  // if the output has been turned on
  if (!outputActive && outputActiveNext) {
    // set the output appropriately
    if (magnetActive) {
      PIN_OUTPUT = PIN_MAGNET;
    }
    else {
      PIN_OUTPUT = PIN_PIEZO;
    }
  }

  // if the output has been turned off
  if (!outputActiveNext && outputActive) {
    // turn off light
    digitalWrite(PIN_COLOR_R, LOW);
    digitalWrite(PIN_COLOR_B, LOW);
  }

  // update output
  outputActive = outputActiveNext;

  if (buttonState != digitalRead(PIN_BUTTON)
      && outputActive) {
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
      digitalWrite(PIN_OUTPUT, HIGH);
      delay(3);
      digitalWrite(PIN_OUTPUT, LOW);
      delay(3);
    }
  }
  else {
    // if we don't want it buzzing just delay
    delay(loops*6);
  }
}

void outputString(String morseMessage) {
  for (int i = 0; i <= morseMessage.length(); i++) {
    if (!outputActive) return;

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

