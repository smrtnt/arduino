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

enum item {
  DEGREE,
  POURCENT,
  POT,
  ARROW,
  ALARM,
  LUMINOSITY
};

static const uint8_t items[6][8] = {
  {
    B11100110,  // XXX__XX_
    B10000110,  // X____XX_
    B10000000,  // X_______
    B10000000,  // X_______
    B10000000,  // X_______
    B10000000,  // X_______
    B11100000,  // XXX_____
    B00000000   // ________
  },
  {
    B11000010,  // XX____X_
    B11000100,  // XX___X__
    B00001000,  // ____X___
    B00010000,  // ___X____
    B00100000,  // __X_____
    B01000110,  // _X___XX_
    B10000110,  // X____XX_
    B00000000   // ________
  },
  {
    B11111110,  // XXXXXXX_
    B11111110,  // XXXXXXX_
    B01111100,  // _XXXXX__
    B01111100,  // _XXXXX__
    B01111100,  // _XXXXX__
    B00111000,  // __XXX___
    B11111110,  // XXXXXXX_
    B00000000   // ________
  },
  {
    B00010000,  // ___X____
    B00010000,  // ___X____
    B00010000,  // ___X____
    B10010010,  // X__X__X_
    B01010100,  // _X_X_X__
    B00111000,  // __XXX___
    B00010000,  // ___X____
    B00000000   // ________
  },
  {
    B11111110,  // XXXXXXX_
    B00000010,  // ______X_
    B11111010,  // XXXXX_X_
    B00001010,  // ____X_X_
    B11101010,  // XXX_X_X_
    B00101010,  // __X_X_X_
    B10101010,  // X_X_X_X_
    B00000000   // ________
  },
  {
    B10010010,  // X__X__X_
    B01010100,  // _X_X_X__
    B00111000,  // __XXX___
    B11111110,  // XXXXXXX_
    B00111000,  // __XXX___
    B01010100,  // _X_X_X__
    B10010010,  // X__X__X_
    B00000000   // ________
  }
};

class LedControlClock: public LedControl {
public:
  LedControlClock(uint8_t p_dataPin, uint8_t p_clkPin, uint8_t p_csPin, uint8_t p_numDevices);
  void displayMinutes(uint8_t p_minutes);
  void displayHours(uint8_t p_hours);
  void displayTemperature(uint8_t p_temperature);
  void displayHumidity(uint8_t p_humidity);
  void displayMoisture(void);
  void setBrightness(uint8_t p_brightness);
};

#endif