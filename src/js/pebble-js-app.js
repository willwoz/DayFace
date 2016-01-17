// uld updated today
Pebble.addEventListener('ready', function() {
  console.log('PebbleKit JS ready!');
});

Pebble.addEventListener('showConfiguration', function() {
  var url = 'https://331bd670.ngrok.io/';

  console.log('Showing configuration page: ' + url);

  Pebble.openURL(url);
});

Pebble.addEventListener('webviewclosed', function(e) {
  var configData = JSON.parse(decodeURIComponent(e.response));
  var datebits = configData.countfrom.split('-');
  
  console.log('Configuration page returned: ' + JSON.stringify(configData));

  if (configData.countfrom) {
    Pebble.sendAppMessage({
      yearfrom: parseInt(datebits[0]),
      dayfrom: parseInt(datebits[2]),
      monthfrom: parseInt(datebits[1]),
      showseconds: praseInt(configData.showseconds),
      showformat: praseInt(configData.format),
      showtriangle: praseInt(configData.showtriabgle)
    }, function() {
      console.log('Send successful!');
    }, function() {
      console.log('Send failed!');
    });
  }
});
