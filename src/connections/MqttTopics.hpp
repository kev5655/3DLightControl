#pragma once

#include <Arduino.h>

#define LIGHT_STATE_SEND_TOPIC "3D-Drucker/LightControl/data/toggle"
#define TEMPERATURE_SEND_TOPIC "3D-Drucker/LightControl/data/temperature"
#define HUMIDITY_SEND_TOPIC "3D-Drucker/LightControl/data/humidity"
#define ERROR_STRING_SEND_TOPIC "3D-Drucker/LightControl/info/errorString"

#define TOGGLE_LIGHT_RECEIVE_TOPIC "3D-Drucker/LightControl/action/toggleLight"
#define SET_INTERVAL_TIME_RECEIVE_TOPIC "3D-Drucker/LightControl/action/setIntervalForSendingData"
