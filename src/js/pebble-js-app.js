Pebble.addEventListener('ready', function() {
  console.log('PebbleKit JS ready!');
});

Pebble.addEventListener('showConfiguration', function() {
  var url = 'https://76e8c1f4.ngrok.io';

  console.log('Showing configuration page: ' + url);

  Pebble.openURL(url);
});

Pebble.addEventListener('webviewclosed', function(e) {
  var configData = JSON.parse(decodeURIComponent(e.response));

  console.log('Configuration page returned: ' + JSON.stringify(configData));

  if (configData.countfrom) {
    Pebble.sendAppMessage({
      countfrom: configData.backgroundColor
    }, function() {
      console.log('Send successful!');
    }, function() {
      console.log('Send failed!');
    });
  }
});
