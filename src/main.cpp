
//#include <ESP8266WiFi.h>
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#include "connections/WifiConnection.hpp"
#include "connections/Mqtt.hpp"



/**************************** Relay Setup ************************************/

#define RELAY_PIN 0
unsigned long lastMillis = 0;

Mqtt * mqtt;


void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Light Controller 3D Drucker\n\n"));


  mqtt = new Mqtt();

  
}


void loop() {

  mqtt->loop();


  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
    mqtt->send("/ESP8266/3DLightControl", "test");
  }
  
}
