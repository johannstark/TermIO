# TermIO - A home-made Indoor temp & humidity measuring device

**TermIO** is a ***home-made*** device for measuring indoor temperature and humidity.

Works with the ***Arduino Nano 33 IoT*** + a ***DHT11 sensor***. It is designed to be as simple as possible.

## Features

-   Temperature and humidity measurement.
-   It computes the Apparent temperature (feels like).
-   Display of the temperature and humidity on 4 digit seven segment display.
-   It uses the NANI WiFi module on the Nano to connect to the internet and send the data to a server/hub/etc.[WIP]

## Hardware

Termy works with the [Arduino Nano 33 IoT](https://store-usa.arduino.cc/products/arduino-nano-33-iot) that Features:
* Built-in WiFi and Low Energy Bluetooth. 
* It is powered by a 32 bit **Arm® Cortex®-M0 Microcontroller**.
* Works with the Arduino Framework.
* It has a **Micro USB** port for power and programming.
* 3.3V logic level.

We use a [DHT11](https://www.adafruit.com/product/386) sensor for measuring temperature and humidity.

Displaying the temperature is done with a generic 4 digit seven segment display.

## Software

C++ Code built with the amazing [PlatformIO IDE](https://platformio.org/) via VS Code.

Libraries used in the project:

* [Adafruit DHT Sensor Library](https://registry.platformio.org/libraries/adafruit/DHT%20sensor%20library)
* [Adafruit Unified Sensor](https://registry.platformio.org/libraries/adafruit/Adafruit%20Unified%20Sensor)
* [SevSeg by Dean Reading](https://registry.platformio.org/libraries/Dean%20Reading/SevSeg)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

***

***Built with Love :heart: in Colombia :colombia:***
