#include "LedControlClock.h"
#include <DS1302.h>
#include "DHT.h"

#define DHTPIN 2 
#define DHTTYPE DHT22  

LedControlClock g_lcc(12, 11, 10, 2);
DHT g_dht(DHTPIN, DHTTYPE);
DS1302 g_rtc(5, 6, 7);
Time g_time = g_rtc.time();


void setup() {
  g_dht.begin();
  g_time = g_rtc.time();
}

void loop() {
  float h = g_dht.readHumidity();
  g_lcc.displayHumidity(h);
  delay(2000);
  float t = g_dht.readTemperature();
  g_lcc.displayTemperature(t);
  delay(2000);
  while(g_time.yr < 2015) {
    g_time = g_rtc.time();
  }
  g_lcc.displayMinutes(g_time.min);
  g_lcc.displayHours(g_time.hr);
  delay(5000);
}
