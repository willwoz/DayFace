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

  var options = {
    countfrom: $countfromDate.val(),
  };

  localStorage.countfrom = options.countfrom;

  console.log('Got options: ' + JSON.stringify(options));
  return options;
}

function loadOptions() {
    var $countfromDate = $('#countfromDate');


    if (localStorage.countfrom) {
        $countfromDate[0].value = localStorage.countfrom;
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