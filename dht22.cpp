#include <DHT.h>

// Define the digital pin connected to the DHT22 data pin
#define DHTPIN 2 

// Define sensor type as DHT22 (AM2302)
#define DHTTYPE DHT22   

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT22 test starting..."));

  dht.begin();
}

void loop() {
  // Wait 2 seconds between measurements (DHT22 has a 0.5Hz to 1Hz sampling rate)
  delay(2000);

  // Reading humidity and temperature
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius
  float fahrenheit = dht.readTemperature(true); // Fahrenheit

  // Check if readings failed and exit early to try again
  if (isnan(humidity) || isnan(temperature) || isnan(fahrenheit)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index
  float hic = dht.computeHeatIndex(temperature, humidity, false);

  // Print results to Serial Monitor
  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperature);
  Serial.print(F("°C ("));
  Serial.print(fahrenheit);
  Serial.print(F("°F)  Heat Index: "));
  Serial.print(hic);
  Serial.println(F("°C"));
}
