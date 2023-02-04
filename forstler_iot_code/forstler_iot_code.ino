#include <BMP280.h>
#include <BH1750.h>
#include <Wire.h>
#include "DHT.h"
#include <OneWire.h>
#include <DallasTemperature.h>

BMP280 bmp280;
BH1750 lightMeter;
DHT dht(33, DHT22);
OneWire oneWire(21);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);

  // BMP280
  Wire.begin(35, 36);
  bmp280.begin();

  // BH1750
  Wire.begin(20, 19);
  lightMeter.begin();

  // DHT
  dht.begin();

  // DallasTemperature
  sensors.begin();

  Serial.println("All sensors are ready");
}

void loop() {
  // BMP280
  uint32_t pressure = bmp280.getPressure();
  float temperatureBmp280 = bmp280.getTemperature();

  // BH1750
  float lux = lightMeter.readLightLevel();

  // DHT
  float humidity = dht.readHumidity();
  float temperatureDht = dht.readTemperature();

  // DallasTemperature
  sensors.requestTemperatures();
  float temperatureDallas = sensors.getTempCByIndex(0);

  //Print the results
  Serial.println("--- BMP280 ---");
  Serial.print("Temperature: ");
  Serial.print(temperatureBmp280);
  Serial.println(" C");
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println("Pa");
  Serial.println();

  Serial.println("--- BH1750 ---");
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  Serial.println();

  Serial.println("--- DHT ---");
  if (!isnan(humidity) && !isnan(temperatureDht)) {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %");
    Serial.print("\tTemperature: ");
    Serial.print(temperatureDht);
    Serial.println(" C");
  } else {
    Serial.println("Failed to read from DHT sensor!");
  }
  Serial.println();

  Serial.println("--- DallasTemperature ---");
  Serial.print("Temperature: ");
  Serial.print(temperatureDallas);
  Serial.println(" C");
  Serial.println();

  delay(5000);
}