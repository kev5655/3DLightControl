#include <Arduino.h>

#include "Relay.hpp"


Relay::Relay(uint8_t pin) {
    this -> pin = pin;
    state = false;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, state);
}

bool Relay::toggle() {
    state = !state;
    digitalWrite(pin, state);
    return state;
}

void Relay::on() {
    state = true;
    digitalWrite(pin, state);
}

void Relay::off() {
    state = false;
    digitalWrite(pin, state);
}

bool Relay::getState() {
    return state;
}



