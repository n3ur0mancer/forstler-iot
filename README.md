# Forstler – IoT Module

Repository for the IoT part of Forstler.

## What is this project about?

This project is about the IoT part of the Forstler system. Forstler is a forest health monitoring and visualisation system. It uses regional data from third party providers and compares it with local data collected by the Forstler IoT module. The code for the single page application part can be found in the [forslter-app](https://github.com/n3ur0mancer/forstler-app) repository.

This project is currently just a mere proof-of-concept and needs further development to be fully functional.

## The Hardware Prototype

### The 3D-Print Files

The following models have been printed in ASA:

- iot-forest-monitor_V1.2
- outter-sensor-lid_V0.2
- outter-sensor-mount_V0.3

The two mounting brackets were printed in TPU:

- iot-forest-monitor-bracket_V2

The "Heltec ESP32+LoRa+OLED case" was designed by Ornotermes, the files are also available on his [printables page](https://www.printables.com/model/78782-heltec-esp32loraoled-case).

### The Bill of Materials (BOM)

An overview of the used materials, tools and electronics to build the IoT prototype can be found in the following [Google Sheet](https://docs.google.com/spreadsheets/d/1dz7JD1OWfYzz5f2v8qW8TEdJs5A8Jh1jVMu9EAY6Yb4/edit?usp=sharing) bill of materials (BOM).

## The software prototype

### Requirements to get started

Download and install the [Arduino IDE](https://www.arduino.cc/en/software/).

It is crucial to use the latest Heltec board profiles in the Arduino IDE, otherwise you will either not find the V3 version of the Heltec board, or you will fail when trying to flash the V2 boards.

Follow the [instructions](https://docs.heltec.org/en/node/esp32/quick_start.html#via-arduino-board-manager) provided by Heltec to install the ESP32-S3 LoRa V3 and updated V2 board profiles and examples. If you simply use the V2 board that is already included in the supported library manager board, the code will have problems compiling.

Install the required libraries:

- Adafruit BMP280 library (by Adafruit)
- BH1750 (by Christopher Laws)
- DallasTemperature (by Miles Burton)
- DHT sensor library (by Adafruit)
- OneWire (by Jim Stud et al.)

Select the correct board and port to flash the ESP32. The port should be straightforward and should appear when you connect your ESP32 to your machine. If not, try downloading the latest drivers from [Silabs](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers). Another all too common but easy to fix problem can be the cable. Particularly the micro-USB cables, which are sometimes power-only and do not transmit data.

Once your port is selected, select the appropriate board profile. For the Heltec ESP32 LoRa V3 select _WiFi LoRa 32(V3) / Wireless shell(V3) / Wireless stick lite (V3)_. For the V2 version of the board select _WiFi LoRa 32(V2)_. Note that it is important that you specifically select _WiFi LoRa 32(V2)_ and not the _Heltec WiFi LoRa 32(V2)_.

### The individual sensor codes

In the _sensors_ directory you will find the individual codes for the different sensors, in case you want to test your sensors individually. A unified sensor code version without the LoRa features is also included.

### Flashing the ESP32s

Once you have set up the requirements, you are ready to flash the ESP32s.

Open the forstler _iot-receiver.ino_ file, which should open automatically in the Arduino IDE. Once open, make sure the correct board and port are selected.

Once you have checked this and everything checks out, you can go ahead and upload the code. By default the baud rate should be 115200, if it is not, select 115200, otherwise you will not be able to decipher the results in the serial monitor.

Open the Serial Monitor (Tools -> Serial Monitor). If the flashing was successful, you should be greeted with `RX mode on....`, and the ESP32's display should show _Waiting for data..._.

Repeat the same process with the _iot-transmitter.ino_ file for the second ESP32. Once flashed, the serial monitor should read:

```
All sensors and LoRa are ready
Sending packet... Length: (number)
TX Done
```

### Testing the Prototype

With both ESP32s powered up, the units should communicate automatically if no configuration has been changed in the code. A quick way to check if the connection was successful is to check the OLED display on the receiver. Approximately every 10 seconds it should read _Received!_.

With the ESP32 receiver connected to your machine, you can open the serial monitor and read the data received. Here is an example of what the received data should look like:

```
Packet received: "DHTTemperature: 22.20, Humidity: 46.60, LUX: 9.17, DallasTemperature: 23.19".
Going into RX mode
```

The RSSI stands for Received Signal Strength Indicator and gives an idea of how good the signal is.

## Bugs to fix & further development

There are a few bugs that need to be fixed in the future:

- The SHA-256 does not match. The problem is well explained by user [ESP_angus](https://www.esp32.com/viewtopic.php?t=10143)
- Problems with incorrect reading of the DS18B20. The initial values are correct, but after some time it tends to default to -127 as the degree Celsius reading.
- This seems to be the cause of the error message: `E (21769) gpio: gpio_set_level(226): GPIO output gpio_num` on the transmitter side that needs to be addressed.
