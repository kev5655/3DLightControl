#pragma once

#include <Arduino.h>


class Relay {

    public:
        Relay(uint8_t pin);
        bool toggle();
        void on();
        void off();
        bool getState();
    private:
        bool state;
        uint8_t pin;
        
};