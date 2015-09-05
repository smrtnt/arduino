#pragma once
#ifndef _MOISTURE_H_
#define _MOISTURE_H_

#include "Arduino.h"

#define MOISTURE_DRY_LEVEL 850

class Moisture {
public:
  Moisture(uint8_t p_sensor_pin);
  bool isDry(void);
private:
  uint8_t m_sensor_pin;
};
#endif