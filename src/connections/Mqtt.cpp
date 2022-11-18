#include <Arduino.h>

#include "Mqtt.hpp"

void messageReceived(String &topic, String &payload) {
    Serial.println("Message Received: " + payload + " from Topic: " + topic);
}

Mqtt::Mqtt(MQTTClientCallbackSimpleFunction func) {
    WiFi.begin("RWD-18719", "ra5t-hmtc-0bwb-ioy7");
    client.begin("192.168.1.138", net);
    client.onMessage(func);
    
    connect();

    client.subscribe("/3D-Drucker/LightControl/action/toggleLight");
    client.subscribe("/3D-Drucker/LightControl/action/setIntervalForSendingData");

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
}

void Mqtt::loop() {
    client.loop();
    if(!client.connected()) {
        connect();
    }
}


// need 0.5 Second for Sending values
void Mqtt::send(String topic, String payload) {
    client.publish(topic, payload);
}