#include <BH1750.h>
#include <Wire.h>

BH1750 lightMeter;

#define SDA_PIN 20
#define SCL_PIN 19

void setup() {
  Serial.begin(115200);

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin(SDA_PIN, SCL_PIN);

  lightMeter.begin();

  Serial.println(F("BH1750 Test begin"));
}

void loop() {
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000);
}