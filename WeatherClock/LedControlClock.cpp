#include "LedControlClock.h"

LedControlClock::LedControlClock(uint8_t p_dataPin, uint8_t p_clkPin, uint8_t p_csPin, uint8_t p_numDevices):
  LedControl(p_dataPin, p_clkPin, p_csPin, p_numDevices) {
    shutdown(0,false);    // wakes up displays
    shutdown(1,false);
    setIntensity(0,2);   // sets intensity levels
    setIntensity(1,2);
    clearDisplay(0);      // clears displays
    clearDisplay(1);}

void LedControlClock::displayMinutes(uint8_t p_minutes) {
  // computes the first and the second digit
  uint8_t left = p_minutes / 10;
  uint8_t right = p_minutes % 10;

  for (uint8_t i = 0; i < 8; i++) {
    uint8_t mask = 0;
    mask = mask | digits[right][i];
    mask = mask | (digits[left][i] << 4);
    setRow(1, i, mask);
  }
}

void LedControlClock::displayHours(uint8_t p_hours) {
  // computes the first and the second digit
  uint8_t left = p_hours / 10;
  uint8_t right = p_hours % 10;

  for (uint8_t i = 0; i < 8; i++) {
    uint8_t mask = 0;
    mask = mask | digits[right][i];
    mask = mask | (digits[left][i] << 4);
    setRow(0, i, mask);
  }
}

void LedControlClock::displayTemperature(uint8_t p_temperature) {
  // computes the first and the second digit
  uint8_t left = p_temperature / 10;
  uint8_t right = p_temperature % 10;

  for (uint8_t i = 0; i < 8; i++) {
    uint8_t mask = 0;
    mask = mask | digits[right][i];
    mask = mask | (digits[left][i] << 4);
    setRow(0, i, mask);
    setRow(1, i, celcius[i]);
  }
}

void LedControlClock::displayHumidity(uint8_t p_humidity) {
  // computes the first and the second digit
  uint8_t left = p_humidity / 10;
  uint8_t right = p_humidity % 10;

  for (uint8_t i = 0; i < 8; i++) {
    uint8_t mask = 0;
    mask = mask | digits[right][i];
    mask = mask | (digits[left][i] << 4);
    setRow(0, i, mask);
    setRow(1, i, pourcent[i]);
  }
}
