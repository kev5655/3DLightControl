#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>


class MqttConnection{

    public:
        bool lightState = 0;
        static MqttConnection * getInstance();
        Adafruit_MQTT_Publish * temperatureData;
        Adafruit_MQTT_Publish * lightStatePubTopic;
        Adafruit_MQTT_Publish * logPubTopic;
        Adafruit_MQTT_Subscribe * toggleLight;
        void setup();
        void loop();

    private:
        uint32_t x = 0;
        static MqttConnection * instance;
        MqttConnection();
        Adafruit_MQTT_Client * mqtt;
        void connect();

    
        

    

};