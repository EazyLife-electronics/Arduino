
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);
  int ddd = dht.readTemperature();
  if (isnan(ddd)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.println(ddd);
}
