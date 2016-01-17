// uld updated today
Pebble.addEventListener('ready', function() {
  console.log('PebbleKit JS ready!');
});

Pebble.addEventListener('showConfiguration', function() {
  var url = 'https://d07388a8.ngrok.io';

  console.log('Showing configuration page: ' + url);

  Pebble.openURL(url);
});

Pebble.addEventListener('webviewclosed', function(e) {
  var configData = JSON.parse(decodeURIComponent(e.response));
  var datebits = configData.countfrom.split('-');
  
  console.log('Configuration page returned: ' + configData.countformat + ' ' + JSON.stringify(configData));

  if (configData.countfrom) {
    Pebble.sendAppMessage({
      yearfrom: parseInt(datebits[0]),
      dayfrom: parseInt(datebits[2]),
      monthfrom: parseInt(datebits[1]),
      showseconds: configData.showseconds,
      showtriangle: configData.showtriangle,
      countformat: parseInt(configData.countformat)
    }, function() {
      console.log('Send successful!');
    }, function() {
      console.log('Send failed!');
    });
  }
});
