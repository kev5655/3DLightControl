#pragma once

#include <Arduino.h>
#include <Bounce2.h>

typedef void (*callbackFunction)(void);

class LightBtn {

    public:
        LightBtn(uint8_t pin);
        void attachClick(callbackFunction func);
        void watch();
    
    private:
        uint8_t pin;
        bool btnIsPressed = false;
        callbackFunction func = NULL;
        Bounce2::Button btn;
};