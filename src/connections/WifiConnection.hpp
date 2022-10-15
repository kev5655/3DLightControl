#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <bits/stdc++.h>

class WifiConnection {

    private:
        WiFiClient client;
    
    public:    
        WifiConnection();
        WiFiClient getClient();
};