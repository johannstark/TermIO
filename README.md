# TermIO

**TermIO** is a ***home-made*** indoor temperature and humidity device. It is a **DIY** project that uses a **DHT11** sensor to measure temperature and humidity and a **4 digit seven segment display/OLED Display** to show the data.

* Version 1 of the device is powered by the ***Arduino Nano 33 IoT*** + a ***DHT11 sensor*** + a ***4 digit seven segment display***.

* Version 2 of the device is powered by the ***ESP8266(Wemos D1 Mini Pro)*** + a ***DHT11 sensor*** + a ***0.91" OLED display***.

## Features

* Temperature and humidity measurement.
* It computes the Apparent temperature (feels like).
* Display of the temperature and humidity on 4 digit seven segment display/OLED Display.
* It uses the NANI WiFi/ESP8266 WiFi module to connect to the internet and send the data to a server/hub/etc. [WIP] :warning:
* Connects to [Homebridge](https://homebridge.io) with a [HTTP Webhook plugin](https://www.npmjs.com/package/homebridge-http-webhooks) to show the data on HomeKit. [WIP] :warning:

## Getting Started

1. Build the circuit using the [schematics](#schematics) based on the board you are using. (Arduino Nano 33 or ESP8266)
2. Clone this repository and open it with the PlatformIO IDE. Be aware to open the right folder depending on your development board.
3. Create `include/secret.h` header file to contain the WiFi credentials to be use by TermIO.
4. Build and upload the code to your development board.

***

## Hardware

TermIO has 2 working versions:

### Arduino Nano 33 IoT

TermIO works with the [Arduino Nano 33 IoT](https://store-usa.arduino.cc/products/arduino-nano-33-iot) that Features:

* Built-in WiFi and Low Energy Bluetooth.

* It is powered by a 32 bit **Arm® Cortex®-M0 Microcontroller**.

* Works with the Arduino Framework.

* It has a **Micro USB** port for power and programming.

* 3.3V logic level.

We use a [DHT11](https://www.adafruit.com/product/386) sensor for measuring temperature and humidity.

Displaying the temperature is done with a generic 4 digit seven segment display.

### ESP8266(Wemos D1 Mini Pro)

***

## Schematics

Here are the main schematics to connect the components to the development board. I suggest to power the entire circuit with a [breadboard power supply](https://www.amazon.com/-/es/ALAMSCN-alimentación-tablero-soldadura-bater%C3%ADa/dp/B08JYPMCZY/ref=sr_1_3?keywords=breadboard+power+supply+module&qid=1672180516&sr=8-3) that delivers both 5V and 3.3V from a 12V socket or USB cable.

**:warning: POWER THE CIRCUIT WITH 3.3V :warning:**

### Arduino Nano 33 IoT

![ArduSchematics](nano33iot/schematics/TermIO%20Schm.png)

### ESP8266(Wemos D1 Mini Pro)

![ESPSchematics](esp8266/schematics/esp8266_schm.png)

## Software

C++ Code built with the amazing [PlatformIO IDE](https://platformio.org/) using the Arduino framework for both Nano 33 IoT and the ESP 8266, via VS Code.

Libraries used in the project:

- [Adafruit DHT Sensor Library](https://registry.platformio.org/libraries/adafruit/DHT%20sensor%20library)
- [Adafruit Unified Sensor](https://registry.platformio.org/libraries/adafruit/Adafruit%20Unified%20Sensor) (Dependency of the DHT Sensor Library)
- [SevSeg by Dean Reading](https://registry.platformio.org/libraries/Dean%20Reading/SevSeg) (Arduino Seven segment display library)
- [Adafruit's GFX and SSD1306 libraries](https://registry.platformio.org/libraries/adafruit/Adafruit%20GFX%20Library) (OLED Display library)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

***

***Built with Love :heart: in Colombia :colombia:***
