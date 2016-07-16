# OTA with the nodeMCU (esp8266)
[Source : ESP8266 Arduino Core](http://esp8266.github.io/Arduino/versions/2.0.0/doc/ota_updates/ota_updates.html#arduino-ide)
[Source : Arduino core for ESP8266 WiFi chip](https://github.com/esp8266/Arduino)

## Steps
- Download and install Arduino IDE
- Start Arduino and open Preferences window.
- Enter http://arduino.esp8266.com/stable/package_esp8266com_index.json into Additional Board Manager URLs field. You can add multiple URLs, separating them with commas.
- Open Boards Manager from Tools > Board menu and install esp8266 platform (and don't forget to select your ESP8266 board from Tools > Board menu after installation).
- Compile and upload the BasicOTA sketch to the serial interface
- Only if the module is connected to the network, the esp8266-ota port will show up in Arduino IDE
- Compile and upload the TestOTA sketch to the new network interface
Normally, the internal led will blink every 1 second.
