# Forstler – IoT Module

Repository for the IoT part of Forstler.

## What is this project about?

This project is the IoT part of the Forstler system. Forstler is a system to monitor and visualize forest health. It uses regional data from thir party providers and compares it with the local data which is being gathered by the Forstler IoT module. The code for the single page application part can be found ine the [forslter-app](https://github.com/n3ur0mancer/forstler-app) repository.

This project is currently just a mere prototype and needs further development to be fully functional.

## The Hardware Prototype

### The 3D-Print Files

The following models were printed in ASA:

- iot-forest-monitor_V1.2
- outter-sensor-lid_V0.2
- outter-sensor-mount_V0.3

The two mounting brackets were printed in TPU:

- iot-forest-monitor-bracket_V2

The "Heltec ESP32+LoRa+OLED case" was designed by Ornotermes, the files are also available on his [printables page](https://www.printables.com/model/78782-heltec-esp32loraoled-case).

### The Bill of Materials (BOM)

An overview of the used materials, tools and electronics to build the IoT prototype can be found in the following [Google Sheet](https://docs.google.com/spreadsheets/d/1dz7JD1OWfYzz5f2v8qW8TEdJs5A8Jh1jVMu9EAY6Yb4/edit?usp=sharing) bill of materials (BOM).

## The Software Prototype

### Prerequisites to get started

Download and install the [Arduino IDE](https://www.arduino.cc/en/software/).

Follow the [instructions](https://docs.heltec.org/en/node/esp32/quick_start.html#via-arduino-board-manager) provided by Heltec to install the ESP32-S3 LoRa V3 board. If you simply use the V2 board that is already included in the supported library manager board, the code will have problems compiling.

Install the necessary libraries:

- Wire
- BH1750

Select the right board and port to flash the ESP32.

### The individual sensor codes

In the directory _individual-sensors_ you will find the singled-out codes for the different sensors, in case you want to test your snesors indiviudally.
