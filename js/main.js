(function() {
  loadOptions();
  submitHandler();
})();

function submitHandler() {
  var $submitButton = $('#submitButton');

  $submitButton.on('click', function() {
    console.log('Submit');

    var return_to = getQueryParam('return_to', 'pebblejs://close#');
    document.location = return_to + encodeURIComponent(JSON.stringify(getAndStoreConfigData()));
  });
}

function getAndStoreConfigData() {
    var $countfromDate = $('#countfromDate');
    var $showsecondsCheckBox = $('#showsecondsCheckBox');
    var $showtriangleCheckBox = $('#showtriangleCheckBox');
    var $formatSelect = $('#formatSelect');
    var $batteryCheckBox = $('#batteryCheckBox');
    var $bluetoothCheckBox = $('#batteryCheckBox');
    var $whiteCheckBox = $('#whiteCheckBox');
    var $showweatherCheckBox = $('#showweatherCheckBox');
    var $showfahrenheitCheckBox = $('#showfahrenheitCheckBox');
    var $weatherpollSlider = $('#weatherpollSlider');
    var $showdateCheckBox = $('#showdateCheckBox');
    var $showlocationCheckBox = $('#showlocationCheckBox');
    var $hourlyCheckBox = $('#hourlyCheckBox');
    var $cleanfaceCheckBox = $('#cleanfaceCheckBox');
    
  var options = {
    countfrom: $countfromDate.val(),
    showseconds: $showsecondsCheckBox[0].checked,
    showtriangle: $showtriangleCheckBox[0].checked,
    countformat: $formatSelect.val(),
    white: $whiteCheckBox[0].checked,
    battery: $batteryCheckBox[0].checked,
    bluetooth: $bluetoothCheckBox[0].checked,
    showweather: $showweatherCheckBox[0].checked,
    showfahrenheit : $showfahrenheitCheckBox[0].checked,
    weatherpoll : $weatherpollSlider.val(),
    showdate : $showdateCheckBox[0].checked,
    showlocation : $showlocationCheckBox[0].checked,
    hourly : $hourlyCheckBox[0].checked,
    cleanface : $cleanfaceCheckBox[0].checked
    showanalogue : $showanalogueCheckBox[0].checked
    showdigital : $showdigitalCheckBox[0].checked
  };

    localStorage.countfrom = options.countfrom;
    localStorage.showseconds = options.showseconds;
    localStorage.showtriangle = options.showtriangle;
    localStorage.countformat = options.countformat;
    localStorage.white = options.white;
    localStorage.battery = options.battery;
    localStorage.bluetooth = options.bluetooth;
    localStorage.showweather = options.showweather;
    localStorage.showfahrenheit = options.showfahrenheit;
    localStorage.weatherpoll = options.weatherpoll;
    localStorage.showdate = options.showdate;
    localStorage.showlocation = options.showlocation;
    localStorage.hourly = options.hourly;
    localStorage.cleanface = options.cleanface;
    localStorage.showanalogue = options.showanalogue;
    localStorage.showdigital = options.showdigital;
    
    console.log('Got options main.js: ' + JSON.stringify(options));
    return options;
}

function loadOptions() {
    var $countfromDate = $('#countfromDate');
    var $showsecondsCheckBox = $('#showsecondsCheckBox');
    var $showtriangleCheckBox = $('#showtriangleCheckBox');
    var $formatSelect = $('#formatSelect');
    var $batteryCheckBox = $('#batteryCheckBox');
    var $bluetoothCheckBox = $('#batteryCheckBox');
    var $whiteCheckBox = $('#whiteCheckBox');
    var $showweatherCheckBox = $('#showweatherCheckBox');
    var $showfahrenheitCheckBox = $('#showfahrenheitCheckBox');
    var $weatherpollSlider = $('#weatherpollSlider');
    var $weatherpollNumber = $('#weatherpollNumber');
    var $showdateCheckBox = $('#showdateCheckBox');
    var $showlocationCheckBox = $('#showlocationCheckBox');
    var $hourlyCheckBox = $('#hourlyCheckBox');
    var $cleanfaceCheckBox = $('#cleanfaceCheckBox');
    var $showanalogueCheckBox = $('#showanalogueCheckBox');
    var $showdigitalCheckBox =$('#showdigitalCheckBox');
    var $showanalogueCheckBox = $('#showanalogueCheckBox');
    var $showdigitalCheckBox =$('#showdigitalCheckBox');

    if (localStorage.countfrom) {
        $countfromDate[0].value = localStorage.countfrom;
        $showsecondsCheckBox[0].checked = (localStorage.showseconds === 'true');
        $showtriangleCheckBox[0].checked = (localStorage.showtriangle === 'true');
        $formatSelect[0].value = localStorage.countformat;
        $batteryCheckBox[0].checked = (localStorage.battery === 'true');
        $bluetoothCheckBox[0].checked = (localStorage.bluetooth === 'true');
        $whiteCheckBox[0].checked = (localStorage.white === 'true');
        $showweatherCheckBox[0].checked = (localStorage.showweather === 'true');
        $showfahrenheitCheckBox[0].checked = (localStorage.showfahrenheit === 'true');
        $weatherpollSlider[0].value = localStorage.weatherpoll;
        $weatherpollNumber[0].value = localStorage.weatherpoll;
        $showdateCheckBox[0].checked = (localStorage.showdate === 'true');
        $showlocationCheckBox[0].checked = (localStorage.showlocation === 'true');
        $hourlyCheckBox[0].checked = (localStorage.hourly === 'true');
        $cleanfaceCheckBox[0].checked = (localStorage.cleanface === 'true');
        $showanalogueCheckBox[0].checked = (localStorage.cleanface === 'true');
        $showdigitalCheckBox[0].checked = (localStorage.cleanface === 'true');
    }
}


function getQueryParam(variable, defaultValue) {
  var query = location.search.substring(1);
  var vars = query.split('&');
  for (var i = 0; i < vars.length; i++) {
    var pair = vars[i].split('=');
    if (pair[0] === variable) {
      return decodeURIComponent(pair[1]);
    }
  }
  return defaultValue || false;
}

/*function loadOptions() {
  var $backgroundColorPicker = $('#backgroundColorPicker');
  var $timeFormatCheckbox = $('#timeFormatCheckbox');

  if (localStorage.backgroundColor) {
    $backgroundColorPicker[0].value = localStorage.backgroundColor;
    $timeFormatCheckbox[0].checked = localStorage.twentyFourHourFormat === 'true';
  }
}

function getAndStoreConfigData() {
  var $backgroundColorPicker = $('#backgroundColorPicker');
  var $timeFormatCheckbox = $('#timeFormatCheckbox');

  var options = {
    backgroundColor: $backgroundColorPicker.val(),
    twentyFourHourFormat: $timeFormatCheckbox[0].checked
  };

  localStorage.backgroundColor = options.backgroundColor;
  localStorage.twentyFourHourFormat = options.twentyFourHourFormat;
  

  console.log('Got options: ' + JSON.stringify(options));
  return options;
}


*/