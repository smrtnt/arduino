#pragma once
#ifndef _LED_CONTROL_CLOCK_H_
#define _LED_CONTROL_CLOCK_H_

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "LedControl.h"

static const uint8_t digits[10][8] = {
  {
    B1110,  // XXX_
    B1010,  // X_X_
    B1010,  // X_X_
    B1010,  // X_X_
    B1010,  // X_X_
    B1010,  // X_X_
    B1110,  // XXX_
    B0000   // ____
  },
  {
    B0010,  // __X_
    B0110,  // _XX_
    B1010,  // X_X_
    B0010,  // __X_
    B0010,  // __X_
    B0010,  // __X_
    B0010,  // __X_
    B0000   // ____
  },
  {
    B1110,  // XXX_
    B0010,  // __X_
    B0010,  // __X_
    B1110,  // XXX_
    B1000,  // X___
    B1000,  // X___
    B1110,  // XXX_
    B0000   // ____
  },
  {
    B1110,  // XXX_
    B0010,  // __X_
    B0010,  // __X_
    B1110,  // XXX_
    B0010,  // __X_
    B0010,  // __X_
    B1110,  // XXX_
    B0000   // ____
  },
  {
    B1010,  // X_X_
    B1010,  // X_X_
    B1010,  // X_X_
    B1110,  // XXX_
    B0010,  // __X_
    B0010,  // __X_
    B0010,  // __X_
    B0000   // ____
  },
  {
    B1110,  // XXX_
    B1000,  // X___
    B1000,  // X___
    B1110,  // XXX_
    B0010,  // __X_
    B0010,  // __X_
    B1110,  // XXX_
    B0000   // ____
  },
  {
    B1110,  // XXX_
    B1000,  // X___
    B1000,  // X___
    B1110,  // XXX_
    B1010,  // X_X_
    B1010,  // X_X_
    B1110,  // XXX_
    B0000   // ____
  },
  {
    B1110,  // XXX_
    B0010,  // __X_
    B0010,  // __X_
    B0100,  // _X__
    B1000,  // X___
    B1000,  // X___
    B1000,  // X___
    B0000   // ____
  },
  {
    B1110,  // XXX_
    B1010,  // X_X_
    B1010,  // X_X_
    B1110,  // XXX_
    B1010,  // X_X_
    B1010,  // X_X_
    B1110,  // XXX_
    B0000   // ____
  },
  {
    B1110,  // XXX_
    B1010,  // X_X_
    B1010,  // X_X_
    B1110,  // XXX_
    B0010,  // __X_
    B0010,  // __X_
    B1110,  // XXX_
    B0000   // ____
  }
};

static const uint8_t celcius[] = {
  B11100110,  // XXX__XX_
  B10000110,  // X____XX_
  B10000000,  // X_______
  B10000000,  // X_______
  B10000000,  // X_______
  B10000000,  // X_______
  B11100000,  // XXX_____
  B00000000   // ________
};

static const uint8_t pourcent[] = {
  B11000010,  // XX____X_
  B11000100,  // XX___X__
  B00001000,  // ____X___
  B00010000,  // ___X____
  B00100000,  // __X_____
  B01000110,  // _X___XX_
  B10000110,  // X____XX_
  B00000000   // ________
};

class LedControlClock: public LedControl {
public:
  LedControlClock(uint8_t p_dataPin, uint8_t p_clkPin, uint8_t p_csPin, uint8_t p_numDevices);
  void displayMinutes(uint8_t p_minutes);
  void displayHours(uint8_t p_hours);
  void displayTemperature(uint8_t p_temperature);
  void displayHumidity(uint8_t p_humidity);
};

#endif