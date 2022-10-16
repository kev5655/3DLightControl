#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>


class WifiConnection {

    private:
        WiFiClient * client = new WiFiClient();
    
    public:    
        WifiConnection();
        WiFiClient * getClient();
};