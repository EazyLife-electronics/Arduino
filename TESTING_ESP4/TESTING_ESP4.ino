#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define I_O_1            LED_BUILTIN
#define I_O_2            D2
#define I_O_3            D3
#define I_O_4            D4

/************************* WIFI Configuration *********************************/

#define WLAN_SSID       "EazyLife"             // Your SSID
#define WLAN_PASS       "eazylife7"        // Your password

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com" //Adafruit Server
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "DEAZYLIFE"            // Username
#define AIO_KEY         "aio_EstY17lNwMlRImaeJ0n6gvFw4iWw"   // Auth Key

//WIFI CLIENT
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe FEED_1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/Centre_Light"); // Feeds name should be same everywhere

//Adafruit_MQTT_Subscribe FEED_2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/Centre_Light"); // Feeds name should be same everywhere
//
//Adafruit_MQTT_Subscribe FEED_3 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/Centre_Light"); // Feeds name should be same everywhere
//
//Adafruit_MQTT_Subscribe FEED_4 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/Centre_Light"); // Feeds name should be same everywhere

char *value;
String message;

void MQTT_connect();

void setup() {
  Serial.begin(115200);

  pinMode(I_O_1, OUTPUT);
  pinMode(I_O_2, OUTPUT);
  pinMode(I_O_3, OUTPUT);
  pinMode(I_O_4, OUTPUT);

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mqtt.subscribe(&FEED_1);
  //  mqtt.subscribe(&FEED_2);
  //  mqtt.subscribe(&FEED_3);
  //  mqtt.subscribe(&FEED_4);
}

void loop() {

  MQTT_connect();


  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(20000))) {

    /********************* CHECK FEED1 ************************/

    if (subscription == &FEED_1) {
      value = (char *)FEED_1.lastread;
      message = String(value);
      message.trim();

      Serial.print(F("Got: "));
      Serial.println(message);

      if (message == "ON") {
        digitalWrite(I_O_1, HIGH);
      }
      else if (message == "OFF") {
        digitalWrite(I_O_1, LOW);
      }
    }

    //    /********************* CHECK FEED2 ************************/
    //
    //    if (subscription == &FEED_2) {
    //      value = (char *)FEED_2.lastread;
    //      message = String(value);
    //      message.trim();
    //
    //      Serial.print(F("Got: "));
    //      Serial.println(message);
    //
    //      if (message == "ON") {
    //        digitalWrite(I_O_2, HIGH);
    //      }
    //      if (message == "OFF") {
    //        digitalWrite(I_O_2, LOW);
    //      }
    //    }

  }
}

void MQTT_connect() {
  int8_t ret;

  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;

  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);
    retries--;
    if (retries == 0) {
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}
