
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#include "connections/WifiConnection.hpp"
#include "connections/MqttConnection.hpp"



/**************************** Relay Setup ************************************/

#define RELAY_PIN 0


void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Light Controller 3D Drucker\n\n"));

  //MqttConnection::getInstance()->setup();
  MqttConnection * mqtt;
  mqtt = MqttConnection::getInstance();
  mqtt->setup();

  /* Relay */
  pinMode(RELAY_PIN, OUTPUT);

}


void loop() {
  //MqttConnection::getInstance()->loop();

}
