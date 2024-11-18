#include <Arduino.h>

#include "SHT.hpp"
#include "connections/Mqtt.hpp"
#include "connections/MqttTopics.hpp"


SHT::SHT(int addr) {
    sht30 = new SHT3X(addr);
    lastMillis = 0;
    interval = 10000;
}

float SHT::getTemp() {
    if(sht30->get() == 0){
        return sht30->cTemp;
    }
    return 0;
}

float SHT::getHumi() {
    if(sht30->get() == 0){
        return sht30->humidity;
    }
    return 0;
}

void SHT::updateIntervalTime(String interval, Mqtt * mqtt) {
    int time = interval.toInt();
    if(time < 1000){
        this->interval = 1000;
        mqtt->send(ERROR_STRING_SEND_TOPIC, "Interval Time ist ein string oder unter 1000 ms, Zeit wurde auf 1000 ms gesetzt");
    } else {
        this->interval = time;
    }
}

void SHT::sendDataByInterval(Mqtt * mqtt) {
    if (millis() - lastMillis > interval) {
        lastMillis = millis();

    
        mqtt->send(
            TEMPERATURE_SEND_TOPIC,
            String(getTemp())
        );

        mqtt->send(
            HUMIDITY_SEND_TOPIC,
            String(getHumi())
        );
    }
}