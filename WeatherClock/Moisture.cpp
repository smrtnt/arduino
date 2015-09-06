#include "Moisture.h"
#include "Logging.h"

Moisture::Moisture(uint8_t p_sensor_pin):
  m_sensor_pin(p_sensor_pin)
  {
}

bool Moisture::isDry(void) {
  uint16_t moistureValue = analogRead(m_sensor_pin);
  TraceInfoFormat(F("Moisture level : %u [0 - 1023]\n"), moistureValue);
  if (moistureValue > MOISTURE_DRY_LEVEL) {
    return true;
  }
  return false;
}