#include "MqttConnection.hpp"

#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include "connections/WifiConnection.hpp"


#define AIO_SERVER      "192.168.1.138"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    ""
#define AIO_KEY         ""


#define RELAY_PIN 0


void toggleLightCallback(char * data, uint16_t len) {
    Serial.print("Trigger toggleLightCallback");
    Adafruit_MQTT_Publish * logPubTopicPtr = MqttConnection::getInstance()->logPubTopic;
    logPubTopicPtr->publish("Trigger toggleLightCallback");
    //for(uint16_t i = 0; i <= len; i++){
    //  Serial.print(data[i]);
    //}
    Serial.println();
    MqttConnection::getInstance()->lightState = !MqttConnection::getInstance()->lightState;
    if(MqttConnection::getInstance()->lightState){
        digitalWrite(RELAY_PIN, LOW);
    } else {
        digitalWrite(RELAY_PIN, HIGH);
    }
    Adafruit_MQTT_Publish * lightStatePubTopicPtr = MqttConnection::getInstance()->lightStatePubTopic;
    lightStatePubTopicPtr->publish(MqttConnection::getInstance()->lightState);
}


MqttConnection::MqttConnection() {
    WifiConnection wifiConnection;
    WiFiClient client = wifiConnection.getClient();
    Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
    this -> mqtt = &mqtt;
    Serial.println("Constructor");
}

MqttConnection * MqttConnection::getInstance() {
    static MqttConnection * instance;
    return instance;
}



void MqttConnection::setup() {
    // Establish Connection
    this-> connect();

    Adafruit_MQTT_Publish publishPtr = Adafruit_MQTT_Publish(this -> mqtt, "kevin/3DDrucker/data");
    this -> temperatureData = &publishPtr;
    publishPtr = Adafruit_MQTT_Publish(this -> mqtt, "kevin/3DDrucker/data/lightState");
    this -> lightStatePubTopic = &publishPtr;
    publishPtr = Adafruit_MQTT_Publish(this -> mqtt, "kevin/3DDrucker/data/lightState");
    this -> logPubTopic = &publishPtr;

    // Setup a feed called 'onoff' for subscribing to changes.
    Adafruit_MQTT_Subscribe subscribePtr = Adafruit_MQTT_Subscribe(this -> mqtt, "kevin/3DDrucker/action/toggleLight", MQTT_QOS_1);
    this -> toggleLight = &subscribePtr;


    // Add Callback
    this -> toggleLight->setCallback(toggleLightCallback);

    // Setup MQTT subscription for onoff feed.
    this -> mqtt->subscribe(this -> toggleLight);
}

void MqttConnection::loop() {
    this -> connect();

    this -> mqtt->processPackets(1000);

    // Now we can publish stuff!
    Serial.print(F("\nSending photocell val "));
    Serial.print(this -> x);
    Serial.print("...");
    if (! this-> temperatureData->publish(this -> x++)) {
        Serial.println(F("Failed"));
    } else {
        Serial.println(F("OK!"));
    }

    if (! this -> mqtt->ping()) {
        this -> mqtt->disconnect();
    }
}

void MqttConnection::connect() {
    int8_t ret;

    // Stop if already connected.
    if (this -> mqtt->connected()) {
        return; 
    }

    Serial.print("Connecting to MQTT... ");

    uint8_t retries = 3;
    while ((ret = (this -> mqtt->connect())) != 0) { // connect will return 0 for connected
        Serial.println(this -> mqtt->connectErrorString(ret));
        Serial.println("Retrying MQTT connection in 5 seconds...");
        this -> mqtt->disconnect();
        delay(5000);  // wait 5 seconds
        retries--;
        if (retries == 0) {
            // basically die and wait for WDT to reset me
            Serial.println("Reset Controller!");
            while (1);
        }
    }
    Serial.println("MQTT Connected!");
}

