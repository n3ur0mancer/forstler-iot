#include "LoRaWan_APP.h"
#include "Arduino.h"
#include <Wire.h>               
#include "HT_SSD1306Wire.h"

SSD1306Wire  esp_display(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED); // addr , freq , i2c group , resolution , rst


#define RF_FREQUENCY                                868000000 // Hz
#define TX_OUTPUT_POWER                             14        // dBm
#define LORA_BANDWIDTH                              0         // [0: 125 kHz, 1: 250 kHz, 2: 500 kHz, 3: Reserved]
#define LORA_SPREADING_FACTOR                       7         // [SF7..SF12]
#define LORA_CODINGRATE                             1         // [1: 4/5, 2: 4/6,   3: 4/7,  4: 4/8]
#define LORA_PREAMBLE_LENGTH                        8         // Same for Tx and Rx
#define LORA_SYMBOL_TIMEOUT                         0         // Symbols
#define LORA_FIX_LENGTH_PAYLOAD_ON                  false
#define LORA_IQ_INVERSION_ON                        false
#define RX_TIMEOUT_VALUE                            1000
#define BUFFER_SIZE                                 30 // Define the payload size here

char txpacket[BUFFER_SIZE];
char rxpacket[BUFFER_SIZE];

static RadioEvents_t RadioEvents;
int16_t txNumber;
int16_t rssi,rxSize;
bool lora_idle = true;

void setup() {
    Serial.begin(115200);
    Mcu.begin();
    
    delay(100);
    esp_display.init();
    esp_display.setTextAlignment(TEXT_ALIGN_LEFT);
    esp_display.setFont(ArialMT_Plain_10);

    txNumber=0;
    rssi=0;
  
    RadioEvents.RxDone = OnRxDone;
    Radio.Init( &RadioEvents );
    Radio.SetChannel( RF_FREQUENCY );
    Radio.SetRxConfig( MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR, LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH, LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,0, true, 0, 0, LORA_IQ_INVERSION_ON, true );
}



void loop()
{
  Radio.IrqProcess( );

  esp_display.clear();
  esp_display.setFont(ArialMT_Plain_24);

  if(lora_idle)
  {
    lora_idle = false;
    Serial.println("RX mode on...");
    Radio.Rx(0);
    esp_display.drawStringMaxWidth(0, 0, 128, "Received! ");
  }
  else
  {
    esp_display.drawStringMaxWidth(0, 0, 128, "Waiting for data...");
  }
  esp_display.display();
  delay(2500);
}



void OnRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr )
{
    rssi=rssi;
    rxSize=size;

    memcpy(rxpacket, payload, size );
    rxpacket[size]='\0';
    Radio.Sleep( );
    Serial.printf("\r\nReceived packet: \"%s\" with rssi %d , length %d\r\n",rxpacket,rssi,rxSize);
		
    lora_idle = true;
}

