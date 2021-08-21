//Viral Science
// www.youtube.com/c/viralscience
//Google Assistant Home Automation
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define Relay1            LED_BUILTIN
//#define Relay2            D2
//#define Relay3            D3
//#define Relay4            D4

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

Adafruit_MQTT_Subscribe Light1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/Centre_Light"); // Feeds name should be same everywhere
//Adafruit_MQTT_Subscribe Light2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Centre_Light");
//Adafruit_MQTT_Subscribe Light3 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Centre_Light");
//Adafruit_MQTT_Subscribe Light4 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Centre_Light");
String message;
void MQTT_connect();

void setup() {
  Serial.begin(115200);

  pinMode(Relay1, OUTPUT);
  //  pinMode(Relay2, OUTPUT);
  //  pinMode(Relay3, OUTPUT);
  //  pinMode(Relay4, OUTPUT);

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

  mqtt.subscribe(&Light1);
  //  mqtt.subscribe(&Light3);
  //  mqtt.subscribe(&Light2);
  //  mqtt.subscribe(&Light4);
}

void loop() {

  MQTT_connect();


  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(20000))) {
    if (subscription == &Light1) {
      Serial.print(F("Got: "));
      char *value = (char *)Light1.lastread;
      message = String(value);
      message.trim();
      Serial.println(message);
      if (message == "ON") {
        digitalWrite(Relay1, HIGH);
      }
      if (message == "OFF") {
        digitalWrite(Relay1, LOW);
      }

    }
    //    if (subscription == &Light2) {
    //      Serial.print(F("Got: "));
    //      Serial.println((char *)Light2.lastread);
    //      char *value = (char *)Light2.lastread;
    //      message = String(value);
    //      message.trim();
    //      if (message == "ON") {digitalWrite(Relay2, HIGH);}
    //      if (message == "OFF") {digitalWrite(Relay2, LOW);}
    //    }
    //    if (subscription == &Light3) {
    //      Serial.print(F("Got: "));
    //      Serial.println((char *)Light3.lastread);
    //      char *value = (char *)Light3.lastread;
    //      message = String(value);
    //      message.trim();
    //      if (message == "ON") {digitalWrite(Relay3, HIGH);}
    //      if (message == "OFF") {digitalWrite(Relay3, LOW);}
    //    }
    //    if (subscription == &Light4) {
    //      Serial.print(F("Got: "));
    //      Serial.println((char *)Light4.lastread);
    //      char *value = (char *)Light4.lastread;
    //      message = String(value);
    //      message.trim();
    //      if (message == "ON") {digitalWrite(Relay4, HIGH);}
    //      if (message == "OFF") {digitalWrite(Relay4, LOW);}
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
