void connectToPort() {
  // connect to port
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
}

void makeRequest() {
  // check if it's connected to a port
  if (!client.connected()) {
    connectToPort();
  }

  // make url string
  String url = "/"+twitterUsername;
  if (lastTweetId != "") {
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
    // find json string because it starts with a [
    if (line.startsWith("[")) {
      processTweets(line);
    }
  }
}

void processTweets(String tweets) {
  Serial.println(tweets);
}

