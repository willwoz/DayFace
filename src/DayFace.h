#pragma once

#include "pebble.h"

#define NUM_CLOCK_TICKS 13
#define NUM_CLOCK_TICKS_WHITE 8
#define NUM_CLOCK_TICKS_RED 13

struct dayface_config {
    uint32_t year;
    uint8_t day;
    uint8_t month;
    uint8_t showseconds; /*show seconds*/
    uint8_t format;  /*days,months,year?*/
    uint8_t showtriangle; /* show triangle */
} __attribute__((__packed__)) global_config;

#define FMT_DAYS    0
#define FMT_MONTHS  1
#define FMT_YEARS   2

#define KEY_COUNTFROM 0

#define KEY_STRUCTURE   0

#define KEY_YEAR        0
#define KEY_DAY         1
#define KEY_MONTH       2
#define KEY_SHOWSECONDS 3
#define KEY_FORMAT      4
#define KEY_SHOWTRIANGLE 5

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
      {68, 0},
      {71, 0},
      {71, 12},
      {68, 12}
    }
  },
  { 4, (GPoint []){
      {72, 0},
      {75, 0},
      {75, 12},
      {72, 12}
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


static const GPathInfo MINUTE_HAND_POINTS = {
  4, (GPoint []) {
    { -3, 20 },
    { 3, 20 },
    { 3, -70 },
    { -3, -70 }
  }
};

static const GPathInfo HOUR_HAND_POINTS = {
  4, (GPoint []){
    {-3, 20},
    {3, 20},
    {3, -50},
    {-3,-50}
  }
};
