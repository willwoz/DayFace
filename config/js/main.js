(function() {
  loadOptions();
  submitHandler();
})();

var formatStrings = ["1 - Days", "2 - Months", "3 - Years", "4 - Zen"];

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

  var options = {
    countfrom: $countfromDate.val(),
    showseconds: $showsecondsCheckBox[0].checked,
    showtriangle: $showtriangleCheckBox[0].checked,
    formatSelect: $formatSelect.val(),
  };

  localStorage.countfrom = options.countfrom;
  localStorage.showseconds = options.showseconds;
  localStorage.showtriangle = options.showtriangle;
  localStorage.formatSelect = options.formatSelect;

  console.log('Got options: ' + JSON.stringify(options));
  return options;
}

function loadOptions() {
    var $countfromDate = $('#countfromDate');
    var $showsecondsCheckBox = $('#showsecondsCheckBox');
    var $showtriangleCheckBox = $('#showtriangleCheckBox');
    var $formatSelect = $('#formatSelect');

    if (localStorage.countfrom) {
        $countfromDate[0].value = localStorage.countfrom;
        $showsecondsCheckBox[0].checked = localStorage.showseconds === 'true';
        $showtriangleCheckBox[0].checked = localStorage.showtriangle === 'true';
        $formatSelect[0].value = localStorage.formatSelect;
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