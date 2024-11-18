#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <MQTT.h>

class Mqtt {

    public:
        Mqtt(MQTTClientCallbackSimpleFunction func);
        void loop();
        void send(String topic, String payload);

    private:
        WiFiClient net;
        MQTTClient client;
        void connect();
        
};