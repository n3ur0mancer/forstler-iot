#include "LoRaWan_APP.h"
#include "Arduino.h"
// #include <BMP280.h>
#include <BH1750.h>
#include <Wire.h>
#include "DHT.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define RF_FREQUENCY                                868000000 // Hz
#define TX_OUTPUT_POWER                             10        // dBm
#define LORA_BANDWIDTH                              0         // [0: 125 kHz, 1: 250 kHz, 2: 500 kHz, 3: Reserved]
#define LORA_SPREADING_FACTOR                       7         // [SF7..SF12]
#define LORA_CODINGRATE                             1         // [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
#define LORA_PREAMBLE_LENGTH                        8         // Same for Tx and Rx
#define LORA_SYMBOL_TIMEOUT                         0         // Symbols
#define LORA_FIX_LENGTH_PAYLOAD_ON                  false
#define LORA_IQ_INVERSION_ON                        false
#define RX_TIMEOUT_VALUE                            1000
#define BUFFER_SIZE                                 30 // Define the payload size here

#define SDA_PIN 19
#define SCL_PIN 20

//BMP280 bmp280;
BH1750 lightMeter;
DHT dht(33, DHT22);
OneWire oneWire(21);
DallasTemperature dallas(&oneWire);

char txpacket[BUFFER_SIZE];
char rxpacket[BUFFER_SIZE];
double txNumber;
bool lora_idle = true;

static RadioEvents_t RadioEvents;
void OnTxDone( void );
void OnTxTimeout( void );

void setup() {
  Serial.begin(115200);
  Mcu.begin();

  // Initialize the I2C bus
  Wire.begin(SDA_PIN, SCL_PIN);

  // BMP280
  // bmp280.begin();

   // DallasTemperature
  dallas.begin();

  // BH1750
  lightMeter.begin();
  delay(50);
  // DHT
  dht.begin();
  delay(50);


  txNumber = 0;

  RadioEvents.TxDone = OnTxDone;
  RadioEvents.TxTimeout = OnTxTimeout;

  Radio.Init( &RadioEvents );
  Radio.SetChannel( RF_FREQUENCY );
  Radio.SetTxConfig( MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                     LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                     LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                     true, 0, 0, LORA_IQ_INVERSION_ON, 3000 );

  Serial.println("All sensors and LoRa are ready");
}

void loop() {
  if (lora_idle == true) {
    delay(10000);

// float temperature = bmp280.getTemperature();
// float pressure = bmp280.getPressure();
dallas.requestTemperatures();
float dallasTemp = dallas.getTempCByIndex(0);
float dhtTemp = dht.readTemperature();
float humidity = dht.readHumidity();
float light = lightMeter.readLightLevel();

sprintf(txpacket, "DHTTemperature: %0.2f, Humidity: %0.2f, LUX: %0.2f, DallasTemperature: %0.2f", dhtTemp, humidity, light, dallasTemp, txNumber); //start a package

Serial.printf("\r\nSending packet... Length: %d\r\n", txpacket, strlen(txpacket));

Radio.Send((uint8_t *) txpacket, strlen(txpacket)); //send the package out
lora_idle = false;
}
Radio.IrqProcess();
}

void OnTxDone( void ) {
Serial.println("TX Done");
lora_idle = true;
}

void OnTxTimeout( void ) {
Radio.Sleep();
Serial.println("TX Timeout");
lora_idle = true;
}
