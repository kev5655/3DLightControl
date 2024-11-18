
#include "connections/Relay.hpp"
#include "connections/SHT.hpp"
#include "connections/LightBtn.hpp"
#include "connections/Mqtt.hpp"
#include "connections/MqttTopics.hpp"



/**************************** Relay Setup ************************************/

// Relay
#define RELAY_PIN 14          // ESP32 Pin: ..., / EPS8266 Pin: 14
Relay * relay;

// Temp Sensor
#define ADDR 0x45
SHT * sht;

// Button
#define BUTTON_PIN 0         // ESP32 Pin: 17, GPIO16 / EPS8266 Pin: 0
LightBtn * btn;

// Connection
Mqtt * mqtt;



void buttonPressed() {
  bool state = relay->toggle();
  String value = "Off";
  if(state) {
    value = "On";
  }
  mqtt->send(LIGHT_STATE_SEND_TOPIC, value);
}

void receivedMqtt(String &topic, String &payload) {
  Serial.println("Message Received: " + payload + " from Topic: " + topic);
  
  if(topic == TOGGLE_LIGHT_RECEIVE_TOPIC) {
    relay->toggle();
  } else if(topic == SET_INTERVAL_TIME_RECEIVE_TOPIC) {
    sht->updateIntervalTime(payload, mqtt);
  }
  
}


void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Light Controller 3D Drucker\n\n"));

  relay = new Relay(RELAY_PIN);
  sht = new SHT(ADDR);
  btn = new LightBtn(BUTTON_PIN);
  btn->attachClick(buttonPressed);
  mqtt = new Mqtt(receivedMqtt);  
}

void loop() {
  mqtt->loop();
  sht->sendDataByInterval(mqtt);
  btn->watch();

}



