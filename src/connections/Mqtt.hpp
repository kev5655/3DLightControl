#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <MQTT.h>

class Mqtt {

    public:
        Mqtt();
        void loop();
        void send(String topic, String payload);

    private:
        WiFiClient net;
        MQTTClient client;
        void connect();
        //void messageReceived(String &topic, String &payload);
        
};