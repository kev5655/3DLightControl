#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <bits/stdc++.h>

#include "WifiConnection.hpp"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "RWD-18719"
#define WLAN_PASS       "ra5t-hmtc-0bwb-ioy7"


WifiConnection::WifiConnection(){
    Serial.println("Setup Connection");

    /* Connection To Wifi */
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

}

WiFiClient WifiConnection::getClient(){
    return this -> client;
}
