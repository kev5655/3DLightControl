#pragma once

#include <WEMOS_SHT3X.h>
#include "connections/Mqtt.hpp"

class SHT {

    public:
        SHT(int addr);
        float getTemp();
        float getHumi();
        void updateIntervalTime(String interval, Mqtt * mqtt);
        void sendDataByInterval(Mqtt * mqtt);
    private:
        unsigned long lastMillis;
        int interval; // Default 10 Sekunden
        SHT3X * sht30;
};



