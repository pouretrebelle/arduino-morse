void connectToPort() {
  // connect to port
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
}

void triggerRequest() {
  // Update timer
  timeSinceLookup = timeSinceStart;

  // Reset button state
  buttonActive = false;

  // Flicker before starting
  for (int i = 0; i < 4; i++) {
    digitalWrite(PIN_COLOR_R, HIGH);
    digitalWrite(PIN_COLOR_B, HIGH);
    delay(100);
    digitalWrite(PIN_COLOR_R, LOW);
    digitalWrite(PIN_COLOR_B, LOW);
    delay(100);
  }
  digitalWrite(PIN_COLOR_R, HIGH);
  digitalWrite(PIN_COLOR_B, HIGH);

  makeRequest(true);
  makeRequest(false);

}

void makeRequest(bool getTweets) {
  // check if it's connected to a port
  if (!client.connected()) {
    connectToPort();
  }

  // make url string
  String url = "/"+twitterUsername;
  if (getTweets) {
    url = "/"+twitterUsername+"/"+lastTweetId;
  }
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(500);
  while(client.available()){
    String line = client.readStringUntil('\r\n');

    // hackety hack hack
    if (line.startsWith("data:")) {
      line = line.substring(5);
      if (getTweets) {
        parseTweets(line);
      } else {
        lastTweetId = line;
      }
    }
  }
}

