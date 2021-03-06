#pragma once

#include "pebble.h"

//#define DO_DEBUG_LOGS
//#define DO_FULL_LOGS
//#define UPDATE_DEBUG

#define STORAGE_VERSION_KEY    99
#define STORAGE_VERSION        7

#define LOW_BATTERY     10

#define NUM_CLOCK_TICKS 13
#define NUM_CLOCK_TICKS_WHITE 8
#define NUM_CLOCK_TICKS_RED 13

struct dayface_config {
    uint32_t year;
    uint32_t countformat;  /*days,months,year?*/
    uint32_t digitalcolor;
    uint8_t day;
    uint8_t month;
    uint8_t showseconds; /*show seconds*/
    uint8_t showtriangle; /* show triangle */
    uint8_t white; /*blac kor white*/
    uint8_t battery; /*show battery*/
    uint8_t bluetooth; /*show bluetooth*/
    uint8_t showweather;
    uint8_t weatherpoll;
    uint8_t showfahrenheit;
    uint8_t showdate;
    uint8_t showlocation;
    uint8_t hourly; /*hourly reminder*/
    uint8_t cleanface;
    uint8_t showanalogue; /*analogue clock*/
    uint8_t showdigital;
    uint8_t wakeup;
    uint8_t bedtime;
    uint8_t saver;
} __attribute__((__packed__)) global_config;

#define WEATHER_POLL_DIV 15
int s_time_to_poll;
int s_weather_updated = 0;

static int s_hourly_done = 0;
static const uint32_t const segments[] = { 200, 400, 200, 400, 200 };

int global_daytime = 1;
int global_seconds = 0;
int global_units_changed;
int new_face;

#define SHAKE_TIME  0

#define FMT_DAYS    1
#define FMT_MONTHS  2
#define FMT_LONG    3
#define FMT_ZEN     4
#define FMT_BLANK   5

#define KEY_COUNTFROM 0


#define KEY_STRUCTURE   0

#define KEY_YEAR            0
#define KEY_DAY             1
#define KEY_MONTH           2
#define KEY_SHOWSECONDS     3
#define KEY_SHOWTRIANGLE    4
#define KEY_FORMAT          5
#define KEY_BLACK           6
#define KEY_BATTERY         7
#define KEY_BLUETOOTH       8
#define KEY_WEATHER         9
#define KEY_FAHRENHEIT      10
#define KEY_WEATHERPOLL     11
#define KEY_SHOWDATE        12
#define KEY_SHOWLOCATION    13
#define KEY_HOURLY          14
#define KEY_CLEANFACE       15
#define KEY_ANALOGUE        16
#define KEY_DIGITAL         17
#define KEY_DIGITALCOLOR    18
#define KEY_TEMPERATURE     20
#define KEY_CONDITIONS      21
#define KEY_LOCATION        22
#define KEY_WAKEUP          23
#define KEY_BEDTIME         24
#define KEY_SAVER           25

#define KEY_TOTAL_KEYS      25

static const uint32_t const digital_color[] = {
    0xFFFFFF, 0xFFFFFF, 0x000000, 0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00, 0xFF00FF
};

static const struct GPathInfo ANALOG_BG_POINTS[] = {
  { 4, (GPoint []){ /*1*/
      {112, 10},
      {114, 12},
      {108, 23},
      {106, 21}
    }
  },
  { 4, (GPoint []){/*2*/
      {132, 47},
      {144, 40},
      {144, 44},
      {135, 49}
    }
  },
   { 4, (GPoint []){/*4*/
      {135, 118},
      {144, 123},
      {144, 126},
      {132, 120}
    }
  },
  { 4, (GPoint []){/*5*/
      {108, 144},
      {114, 154},
      {112, 157},
      {106, 147}
    }
  },
  { 4, (GPoint []){/*7*/
      {32, 10},
      {30, 12},
      {36, 23},
      {38, 21}
    }
  },
  { 4, (GPoint []){/*8*/
      {12, 47},
      {-1, 40},
      {-1, 44},
      {9, 49}
    }
  },
  { 4, (GPoint []){/*10*/
      {9, 118},
      {-1, 123},
      {-1, 126},
      {12, 120}
    }
  },
  { 4, (GPoint []){/*11*/
      {36, 144},
      {30, 154},
      {32, 157},
      {38, 147}
    }
  },
  { 4, (GPoint []) { /*12*/
      {69, 0},
      {71, 0},
      {71, 12},
      {69, 12}
    }
  },
  { 4, (GPoint []){
      {73, 0},
      {75, 0},
      {75, 12},
      {73, 12}
    }
  },
 { 4, (GPoint []){/*3*/
      {144, 82},
      {156, 82},
      {156, 84},
      {144, 84}
    }
  },
  { 4, (GPoint []){/*6*/
      {70, 155},
      {73, 155},
      {73, 167},
      {70, 167}
    }
  },
  { 4, (GPoint []){/*9*/
      {-14, 82},
      {-2, 82},
      {-2, 84},
      {-14, 84}
    }
  }
};

static const GPathInfo TRIANGLE_POINTS = {
    3, (GPoint []) {
        { 90, 10 },
        { 20, 130 },
        { 160, 130 }
    }
};

static const GPathInfo BT_POINTS = {
    6, (GPoint []) {
        { 1, 5 },
        { 20, 15 },
        { 10, 20 },
        { 10,1 },
        { 20, 5},
        { 1, 15}
    }
};

static const GPathInfo MINUTE_HAND_POINTS = {
  4, (GPoint []) {
    { -3, 20 },
    { 3, 20 },
    { 3, -65 },
    { -3, -65 }
  }
};

static const GPathInfo HOUR_HAND_POINTS = {
  4, (GPoint []){
    {-3, 20},
    {3, 20},
    {3, -45},
    {-3,-45}
  }
};

static const GPathInfo *HOUR_HAND_POINTS_ARRAY[2] = { &HOUR_HAND_POINTS, &HOUR_HAND_POINTS };
