void parseTweets(String tweets) {
  // if there are multiple tweets loop through them
  while (tweets.indexOf(" --- ") != -1) {
    int index = tweets.indexOf(" --- ");
    String tweet = tweets.substring(0, index);
    incoming.push_back(tweet);
    Serial.println(tweet);
    tweets = tweets.substring(index + 5);
  }
  // send the last tweet and set pending to true
  if (tweets.length() > 0) {
    incoming.push_back(tweets);
    Serial.println(tweets);
    messagesPending = true;
  }
}

