# Basic example to pub/sub to cloudMQTT.com with WifiClientSecure - ESP8266

## Steps
- Download the MQTT pubsubclient library from [GitHub](https://github.com/knolleary/pubsubclient/releases/tag/v2.6)
- Create a account and a user at [https://www.cloudmqtt.com](https://www.cloudmqtt.com)
- Install this [plugin](https://github.com/esp8266/arduino-esp8266fs-plugin) to load files into the board
- Create a folder called "data" into this sketch and generate your certificate with OpenSSL (openssl req -sha256 -newkey rsa:2048 -keyout privateKey.pem -out caCert.pem -days 1095 -x509)
- Copy only the caCert.pem into this folder



