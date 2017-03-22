'use strict';

var Twitter = require('twitter');
var express = require('express');
var deasync = require('deasync');
var env = require('dotenv').config();

// setup server
var app = express();

// health check
var healthcheck = {
  version: require('./package').version,
  http: 'okay'
};
// healthcheck info public
app.get(['/healthcheck'], function(req, res) {
  res.jsonp(healthcheck);
});

// setup twitter client
var client = new Twitter({
  consumer_key: process.env.CONSUMER_KEY,
  consumer_secret: process.env.CONSUMER_SECRET,
  access_token_key: process.env.ACCESS_TOKEN_KEY,
  access_token_secret: process.env.ACCESS_TOKEN_SECRET
});

// latest mentioned tweet ID
function latestId(req, res, next) {
  res.setTimeout(0);
  res.send('data:'+getLatestId(req.params.username));
}
function getLatestId(username) {
  var ret;
  var params = {
    result_type: 'recent',
    q: '@'+username,
    count: 1,
    include_entities: false,
  };
  client.get('search/tweets.json', params, function(error, data, response) {
    if (!error) {
      ret = data.statuses[0].id_str;
    }
    else {
      ret = false;
    }
  });
  deasync.loopWhile(function(){ return ret === undefined });
  return ret;
}

// main function
function twitterData(req, res, next) {
  res.setTimeout(0);
  var data = getTweets(req.params.username, req.params.sinceId);
  res.send('data:'+data);
};
// get tweets
function getTweets(username, sinceId) {
  var json = [];
  var ret;

  var params = {
    result_type: 'recent',
    q: '@'+username,
    include_entities: false,
    since_id: sinceId,
    count: 100,
  };

  client.get('search/tweets.json', params, function(error, data, response) {
    if (!error) {
      for (var i = 0; i < data.statuses.length; i++) {
        if (data.statuses[i].id != sinceId) {
          json.push(tweetData(data.statuses[i], username));
        }
      }
      ret = json.reverse().join(' --- ');
    }
    else {
      ret = false;
    }
  });

  deasync.loopWhile(function(){return ret === undefined});
  return ret;
}

// sanitise tweets
function tweetData(tweet, username) {
  let text = tweet.text;
  let firstMetion = new RegExp('^(@'+username+' )');
  let otherMentions = new RegExp('@'+username, 'g');
  text = text.replace(firstMetion, "").replace(otherMentions, "@me");
  return tweet.user.screen_name+'--'+text;
}

// deal w/ the routing
app.route('/:username/:sinceId').get(twitterData);
app.route('/:username').get(latestId);

// start the server
var server = app.listen(process.env.PORT || 2000, function () {
  var host = server.address().address;
  var port = server.address().port;
  console.log('Example app listening at http://%s:%s', host, port);
});
server.timeout = 0;
