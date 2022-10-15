#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>


class MqttConnection{
    private:
        uint32_t x = 0;
        static MqttConnection * instance;
        Adafruit_MQTT_Client * mqtt;
        void connect();
        

    public:
        bool lightState = 0;
        MqttConnection();
        static MqttConnection * getInstance();
        Adafruit_MQTT_Publish * temperatureData;
        Adafruit_MQTT_Publish * lightStatePubTopic;
        Adafruit_MQTT_Publish * logPubTopic;
        Adafruit_MQTT_Subscribe * toggleLight;
        void setup();
        void loop();

};