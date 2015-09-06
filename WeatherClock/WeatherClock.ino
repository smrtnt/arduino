/**
 * 
 * Project:       WeatherClock
 * 
 * Abstract:      Clock + Weather + Alarm + Moisture 
 * 
 * Purpose:       -
 * 
 * Author:        Samuel Mertenat - samuel.mertenat@edu.hefr.ch
 * Date:          August 2015
 * 
 * Libraries:     - DS1307RTC:   http://www.pjrc.com/teensy/td_libs_DS1307RTC.html
 *                - Time:        https://www.pjrc.com/teensy/td_libs_Time.html
 *                - TimeAlarms:  https://www.pjrc.com/teensy/td_libs_TimeAlarms.html
 *                - DHT:         https://github.com/adafruit/DHT-sensor-library
 *                - LedControl:  https://github.com/wayoda/LedControl
 *                - Encoder:     https://www.pjrc.com/teensy/td_libs_Encoder.html#optimize
 *
 * Components:    - 1x Arduino Nano
 *                - 2x LED matrices (8 x 8)
 *                - 1x RTC (DS1307)
 *                - 1x DHT11
 *                - 1x Active buzzer
 *                - 1x Photoresistor
 *                - 1x Moisture sensor
 * 
 * Connections:   - LED matrices:    10 - 11 - 12
 *                - RTC:             A4 - A5
 *                - DHT11:           8
 *                - Active buzzer    6
 *                - Photoresistor    A0
 *                - Moisture sensor: A1
 *
 * TO DO:         - Alarm
 *                - Menu for settings (alarm on / off, ...)
 */

#include "LedControlClock.h"
#include "DHT.h"
#include <DS1307RTC.h>
#include <Time.h>
#include <TimeAlarms.h>
#include <Wire.h>
#include "Logging.h"
#include "Button.h"
#include "Moisture.h"


#define DHTPIN 8 
#define DHTTYPE DHT11  

// logging level
// 1: error, 2: error + info, 3: error + info + debug
int g_loggingLevel = 3;

LedControlClock g_lcc(12, 11, 10, 2);
DHT g_dht(DHTPIN, DHTTYPE);
button g_button(4); 
Moisture g_moisture(1);

uint8_t g_hours = 0;
uint8_t g_minutes = 0;

uint8_t g_brightnessLevel = 15;

void setup() {
  Serial.begin(9600);  
  g_dht.begin();

  setSyncProvider(RTC.get); 
  if (timeStatus() != timeSet) {
    TraceInfo(F("Unable to sync with the DS1307\n"));
  } else {
    TraceInfoFormat(F("Time set to : %u:%u\n"), hour(), minute());
  }

  // attaches the functions called on one or double-click
  g_button.attach_fnct_on_click(one_click);

  g_lcc.setBrightness(g_brightnessLevel);
}

void loop() {
  // updates the clock if necessary
  if (timeStatus() == timeSet) {
    if (hour() != g_hours || minute() != g_minutes) {
      g_hours = hour();
      g_minutes = minute();
      displayTime();
    }
  }

  g_button.tick();

  if (g_moisture.isDry()) {
    g_lcc.displayMoisture();
    delay(1000);
    displayTime();
  }
}

// function called on one-click
void one_click() {
  float h = g_dht.readHumidity();
  g_lcc.displayHumidity(h);
  delay(6000);
  float t = g_dht.readTemperature();
  g_lcc.displayTemperature(t);
  delay(6000);
  displayTime();
  TraceInfo(F("Button: One-click\n"));
}

void displayTime(void) {
  g_lcc.displayHours(g_hours);
  g_lcc.displayMinutes(g_minutes);
}
