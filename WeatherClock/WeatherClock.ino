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
//#include <Encoder.h>
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
//Encoder g_enc(2, 3);
button g_button(4); 
Moisture g_moisture(1);

long g_encoderPosition = 0;

uint8_t g_hours = 0;
uint8_t g_minutes = 0;

uint8_t g_brightnessLevel = 1;

// state-machine;
// enum states {
//   STATE_NO_ACTION,
//   STATE_TEMP_HUM,
//   STATE_BRIGHTNESS,
//   NB_OF_STATES
// };

// uint8_t g_currentState = 0; // no action
// long g_lastAction = 0; // millis() of last action
// const uint8_t TIME_OUT = 3000; // timeout
// bool g_menuDisplayed = false;

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
  //g_button.attach_fnct_on_double_click(double_click);

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
  /*long newPosition = g_enc.read();
  if (newPosition != g_encoderPosition) {
    g_encoderPosition = newPosition;
    TraceInfoFormat(F("Position: %u\n"), g_encoderPosition);
  }*/
  g_button.tick();

  // reads the photoresistor
  /*
  uint16_t photoresistorValue = analogRead(A1);    
  TraceInfoFormat(F("Photoresistor: %u\n"), photoresistorValue);
  delay(100);
  */
}

// function called on one-click
void one_click() {
  // on a single click --> display temp & hum
  // if (g_menuDisplayed == false) 
  //   g_currentState = STATE_TEMP_HUM;

  // switch (g_currentState) {
  //   // displays humidity & temperature
  //   case STATE_TEMP_HUM:
  //     float h = g_dht.readHumidity();
  //     g_lcc.displayHumidity(h);
  //     delay(1500);
  //     float t = g_dht.readTemperature();
  //     g_lcc.displayTemperature(t);
  //     delay(1500);
  //     displayTime();
  //     break;

  //   //default:
  // }
  float h = g_dht.readHumidity();
  g_lcc.displayHumidity(h);
  delay(1500);
  float t = g_dht.readTemperature();
  g_lcc.displayTemperature(t);
  delay(1500);
  displayTime();
  TraceInfo(F("Button: One-click\n"));
}

// function called on double-click
// void double_click() {
//   TraceInfo(F("Button: Double-click\n"));
//   g_menuDisplayed = true;
//   while (g_menuDisplayed == true || (millis() - g_lastAction) < TIME_OUT) {
//     long newPosition = g_enc.read();
//     if (newPosition != g_encoderPosition) {
//       if (newPosition > g_encoderPosition)
//         g_currentState = (g_currentState + 1) % NB_OF_STATES;
//       else
//         if (g_currentState > 0)
//           g_currentState--;
//         else 
//           g_currentState = NB_OF_STATES - 1;
//       g_encoderPosition = newPosition;
//       g_lastAction = millis();
//       TraceInfoFormat(F("State: %u\n"), g_currentState);
//     }
//     g_button.tick();
//   }
// }

void displayTime(void) {
  g_lcc.displayHours(g_hours);
  g_lcc.displayMinutes(g_minutes);
}
