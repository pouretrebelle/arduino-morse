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
  morseLoop();
}

