#include <Arduino.h>

#include "Mqtt.hpp"
#include "Secret.hpp"
#include "MqttTopics.hpp"

Mqtt::Mqtt(MQTTClientCallbackSimpleFunction func)
{
    WiFi.begin(SECRET_SSID, SECRET_PASS);
    nasClient.begin(NAS_IP, net);
    nasClient.onMessage(func);

    octoPrintClient.begin(OCTO_PRINT_IP, net);

    connect();

    nasClient.subscribe(TOGGLE_LIGHT_RECEIVE_TOPIC);
    nasClient.subscribe(SET_INTERVAL_TIME_RECEIVE_TOPIC);
}

void Mqtt::connect()
{
    Serial.print("checking wifi...");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }

    Serial.print("\nconnecting to nas...");
    while (!nasClient.connect("3DLightControl", MQTT_NAS_USER, MQTT_NAS_PASS))
    {
        Serial.print(".");
        delay(1000);
    }

    Serial.print("\nconnected!\nconnecting to octo print...");
    while (!octoPrintClient.connect("3DLightControl",
                                    MQTT_OCTO_PRINT_USER, MQTT_OCTO_PRINT_PASS))
    {
        Serial.print(".");
        delay(1000);
    }

    Serial.println("\nconnected!");
}

void Mqtt::loop()
{
    nasClient.loop();
    if (!nasClient.connected())
    {
        connect();
    }
    octoPrintClient.loop();
    if (!octoPrintClient.connected())
    {
        connect();
    }
}

// need 0.5 Second for Sending values
void Mqtt::send(String topic, String payload)
{
    nasClient.publish(topic, payload);
    octoPrintClient.publish(topic, payload);
}