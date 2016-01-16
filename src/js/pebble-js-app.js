Pebble.addEventListener('ready', function() {
  console.log('PebbleKit JS ready!');
});

Pebble.addEventListener('showConfiguration', function() {
  var url = 'https://f9cd91d1.ngrok.io/';

  console.log('Showing configuration page: ' + url);

  Pebble.openURL(url);
});

Pebble.addEventListener('webviewclosed', function(e) {
  var configData = JSON.parse(decodeURIComponent(e.response));
  var datebits = configData.countfrom.split('-');
  
  console.log('Configuration page returned: ' + JSON.stringify(configData));

  if (configData.countfrom) {
    Pebble.sendAppMessage({
      dayfrom: parseInt(datebits[2]),
      monthfrom: parseInt(datebits[1]),
      yearfrom: parseInt(datebits[0])
    }, function() {
      console.log('Send successful!');
    }, function() {
      console.log('Send failed!');
    });
  }
});
