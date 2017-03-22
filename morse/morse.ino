#include <QList.h>
#include "QList.cpp"
#include <ESP8266WiFi.h>

// Define LED pins
int PIN_COLOR_R = 13;
int PIN_COLOR_B = 12;

// Define button pin and states
int PIN_BUTTON = 16;
bool buttonState = false;
bool buttonActive = false;

// Define dial pin and state
int dialRead = 0;
int PIN_DIAL = A0;

// Define output pins and states
int PIN_PIEZO = 15;
int PIN_MAGNET = 14;
int PIN_OUTPUT;
int PIN_TOGGLE_PIEZO = 4;
int PIN_TOGGLE_MAGNET = 5;
bool piezoActive = false;
bool magnetActive = false;
bool outputActive = false;
int buzzSpeed = 20;

// Initialise message list
QList<String> incoming;
bool messagesPending = false;

// Define wifi things
const char* ssid = "SKYD237F";
const char* password = "YVUFPPDC";
const char* host = "tweet-grabber.glitch.me";
WiFiClient client;
String lastTweetId = "844298004786036736";
String twitterUsername = "charlottesbot";

void setup(void) {
  incoming.push_back("SOS");
  messagesPending = true;

  // Set pin modes
  pinMode(PIN_COLOR_R, OUTPUT);
  pinMode(PIN_COLOR_B, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_DIAL, INPUT);
  pinMode(PIN_MAGNET, OUTPUT);
  pinMode(PIN_PIEZO, OUTPUT);
  pinMode(PIN_TOGGLE_MAGNET, INPUT);
  pinMode(PIN_TOGGLE_PIEZO, INPUT);

  // Connect to wifi
  Serial.begin(115200);
  delay(100);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void loop(void) {
  makeRequest();
  morseLoop();
}

