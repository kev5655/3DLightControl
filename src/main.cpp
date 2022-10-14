/***************************************************
  Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#include "Connection.hpp"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "RWD-18719"
#define WLAN_PASS       "ra5t-hmtc-0bwb-ioy7"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "192.168.1.138"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    ""
#define AIO_KEY         ""

/**************************** Relay Setup ************************************/

#define RELAY_PIN 0
bool lightState = false;

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiClientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish temperatureData = Adafruit_MQTT_Publish(&mqtt, "kevin/3DDrucker/data");
Adafruit_MQTT_Publish lightStatePubTopic = Adafruit_MQTT_Publish(&mqtt, "kevin/3DDrucker/data/lightState");
Adafruit_MQTT_Publish logPubTopic = Adafruit_MQTT_Publish(&mqtt, "kevin/3DDrucker/log");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe toggleLight = Adafruit_MQTT_Subscribe(&mqtt, "kevin/3DDrucker/action/toggleLight", MQTT_QOS_1);

/*************************** Sketch Code ************************************/

void MQTT_connect();

void toggleLightCallback(char *data, uint16_t len) {
  Serial.print("Trigger toggleLightCallback");
  logPubTopic.publish("Trigger toggleLightCallback");
  //for(uint16_t i = 0; i <= len; i++){
  //  Serial.print(data[i]);
  //}
  //Serial.println();
  lightState = !lightState;
  if(lightState){
    digitalWrite(RELAY_PIN, LOW);
  } else {
    digitalWrite(RELAY_PIN, HIGH);
  }

  lightStatePubTopic.publish(lightState);
}

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Light Controller 3D Drucker\n\n"));

  /* Connection To Wifi */
  Serial.print("Connecting to: ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.print("IP address: "); Serial.println(WiFi.localIP());

  //Add Callback
  toggleLight.setCallback(toggleLightCallback);

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&toggleLight);

  /* Connection To MQTT */
  MQTT_connect();

  /* Relay */
  pinMode(RELAY_PIN, OUTPUT);

}

uint32_t x=0;

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  mqtt.processPackets(1000);


  // Now we can publish stuff!
  Serial.print(F("\nSending photocell val "));
  Serial.print(x);
  Serial.print("...");
  if (! temperatureData.publish(x++)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }

  if(! mqtt.ping()) {
      mqtt.disconnect();
    }

}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
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