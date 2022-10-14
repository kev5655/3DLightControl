#include <Arduino.h>

#include "Connection.hpp"

void Connection:setup(){
    
    Serial.println(F("Light Controller 3D Drucker\n\n"));

    // Connect to WiFi access point.

    Serial.print("Connecting to: ");
    Serial.println(WLAN_SSID);

    WiFi.begin(WLAN_SSID, WLAN_PASS);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    Serial.println();

    Serial.println("WiFi connected");
    Serial.print("IP address: "); Serial.println(WiFi.localIP());

    //Add Callback
    toggleLight.setCallback(toggleLightCallback);

    // Setup MQTT subscription for onoff feed.
    mqtt.subscribe(&toggleLight);
}
