#include <Arduino.h>

#include "Mqtt.hpp"

void messageReceived(String &topic, String &payload) {
    Serial.println("Message Received: " + payload + " from Topic: " + topic);
}

Mqtt::Mqtt() {
    WiFi.begin("RWD-18719", "ra5t-hmtc-0bwb-ioy7");
    client.begin("192.168.1.138", net);
    client.onMessage(messageReceived);
    connect();
}

void Mqtt::connect() {
    Serial.print("checking wifi...");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }

    Serial.print("\nconnecting...");
    while (!client.connect("arduino", "public", "public"))
    {
        Serial.print(".");
        delay(1000);
    }

    Serial.println("\nconnected!");

    client.subscribe("/hello");
}

void Mqtt::loop() {
    client.loop();
    if(!client.connected()) {
        connect();
    }
}

void Mqtt::send(String topic, String payload) {
    client.publish(topic, payload);
}