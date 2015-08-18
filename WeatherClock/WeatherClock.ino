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
 */

#include "LedControlClock.h"
#include "DHT.h"
#include <DS1307RTC.h>
#include <Time.h>
#include <Wire.h>
#include <Encoder.h>
#include "Logging.h"
#include "Button.h"


#define DHTPIN 8 
#define DHTTYPE DHT11  

// logging level
// 1: error, 2: error + info, 3: error + info + debug
int g_loggingLevel = 3;

LedControlClock g_lcc(12, 11, 10, 2);
DHT g_dht(DHTPIN, DHTTYPE);
Encoder g_enc(2, 3);
button g_button(4); 


long g_encoderPosition = 0;

uint8_t g_hours = 0;
uint8_t g_minutes = 0;

void setup() {
  TraceInfo(F("The WeatherClock is starting..."));
  Serial.begin(9600);  
  g_dht.begin();

  // attaches the functions called on one or double-click
  g_button.attach_fnct_on_click(one_click);
  g_button.attach_fnct_on_double_click(double_click);
}

void loop() {
  tmElements_t tm;
  if (RTC.read(tm)) {
    if (tm.Minute != g_minutes || tm.Hour != g_hours) {
      g_minutes = tm.Minute;
      g_hours = tm.Hour;
      g_lcc.displayHours(g_hours);
      g_lcc.displayMinutes(g_minutes);
      TraceInfoFormat(F("Time: %u:%u\n"), g_hours, g_minutes);
    }
  } else {
    TraceError(F("ERROR: The DS1307 is stopped or is not working"));
  }
  long newPosition = g_enc.read();
  if (newPosition != g_encoderPosition) {
    g_encoderPosition = newPosition;
    TraceInfoFormat(F("Position: %u\n"), g_encoderPosition);
  }
  g_button.tick();
}

// function called on one-click
void one_click() {
  float h = g_dht.readHumidity();
  g_lcc.displayHumidity(h);
  delay(1500);
  float t = g_dht.readTemperature();
  g_lcc.displayTemperature(t);
  delay(1500);
  g_lcc.displayHours(g_hours);
  g_lcc.displayMinutes(g_minutes);
  TraceInfo(F("Button: One-click\n"));
}

// function called on double-click
void double_click() {
  TraceInfo(F("Button: Double-click\n"));
}
