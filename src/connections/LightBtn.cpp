#include <Arduino.h>
#include <Bounce2.h>

#include "LightBtn.hpp"


LightBtn::LightBtn(uint8_t pin) {
    this -> pin = pin;
    btn = Bounce2::Button();
    btn.attach(pin, INPUT);
    btn.interval(5);
}


void LightBtn::attachClick(callbackFunction func) {
    this->func = func;
}

void LightBtn::watch() {
    btn.update();

    if(btn.pressed()){
        func();
    }

    // if(digitalRead(pin) && !btnIsPressed){
    //     btnIsPressed = true;
        
    // }

    // if(! digitalRead(pin)) {
    //     btnIsPressed = false;
    // }
}