// simple project using Arduino UNO and Matrix LED Display MAX7219 with u8g2 library
// and RTC (real time clock) module to display time

// created by upir, 2023
// youtube channel: https://www.youtube.com/upir_upir

// YOUTUBE VIDEO: https://youtu.be/50bVXHYW_9Q
// Source files: https://github.com/upiir/arduino_wood_clock

// links from the video:
// Atezr laser cutter for enclosure: https://atezr.com/pages/genesis-engrave-l2-laser-engraver
// Laser fixing pins: https://s.click.aliexpress.com/e/_DDydZoJ
// Honeycomb table: https://s.click.aliexpress.com/e/_DBxuFw7
// Wood veneer yellow: https://s.click.aliexpress.com/e/_Dl2y0WP
// Wood veneer red: https://s.click.aliexpress.com/e/_Dkl2Wwn
// Wood veneer brown: https://s.click.aliexpress.com/e/_DeqjsZN
// LED Matrix display: https://s.click.aliexpress.com/e/_DlnFAYz
// WOKWI display documentation: https://docs.wokwi.com/parts/wokwi-max7219-matrix
// U8g2 + Matrix display screenshot: https://github.com/olikraus/u8g2/wiki/gallery#28-may-2017-max7219-32x8-led-matrix
// U8g2 fonts: https://github.com/olikraus/u8g2/wiki/fntlist8#7-pixel-height

// Related videos with similar dot matrix displays:
// Why are pixels square? - https://youtu.be/oLgUtjyKO6Q
// Arduino + Matrix Display - https://youtu.be/jlhcDzS17vU
// 51 years old display! - https://youtu.be/PBaL9w5w-2c
// 1 DISPLAY 3 SENSORS - https://youtu.be/lj_7UmM0EPY
// DIY Battery Indicator - https://youtu.be/Mq0WBPKGRew
// Smooth Arduino 16x2 Gauge - https://youtu.be/cx9CoGqpsfg
// Arduino Gauge in 11 Minutes - https://youtu.be/upE17NHrdPc


#include <Arduino.h>
#include <U8g2lib.h>
#include "RTClib.h"

RTC_DS1307 rtc; // set the real time clock module

U8G2_MAX7219_32X8_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 11, /* data=*/ 12, /* cs=*/ 10, /* dc=*/ U8X8_PIN_NONE, /* reset=*/ U8X8_PIN_NONE);

char time_string[10]; // string to hold the current time to be displayed

void setup(void) {

  pinMode(4, OUTPUT); // we are using pin 4 to power the real time clock module, 
  digitalWrite(4, HIGH); // since the +5V pin is already used for the display
  
  u8g2.begin(); // begin function is required for u8g2 library
  u8g2.setContrast(200); // set display contrast 0-255

  if (! rtc.begin()) { // start the RTC module
    abort();
  }

  // following line sets the RTC to the date & time this sketch was compiled
  // uncomment this when uploading to Arduino, otherwise the time will be 0:00 and not increasing
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

}

void loop(void) {

  DateTime now = rtc.now(); // get current time

  sprintf(time_string, "%d:%02d", now.hour(), now.minute()); // add hours, colon symbol and minutes into a string

  u8g2.setFont(u8g2_font_t0_11b_tn);  // choose a suitable font

  u8g2.clearBuffer(); // clear the internal u8g2 memory
  u8g2.drawStr(2, 8, time_string);  // draw the time string to the display
  u8g2.sendBuffer(); // transfer internal memory to the display
  delay(1000); // wait one second

}
