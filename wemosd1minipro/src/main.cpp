// Libraries
#include <SevSeg.h>
#include <DHT.h>
#include <WiFiNINA.h>

// Headers
#include "secret.h"

// Pin definitions
#define SENSOR_PIN 17

// Temp Sensor & 4 digit seven segment display instances
DHT dht(SENSOR_PIN, DHT11);
SevSeg sevseg; //Instantiate a seven segment object

// Variable definition
long sensor_timer = 250;
long prev_time = 0;
float prev_reading = 0;
float feels_like = 0;
char res[] = {};

// WiFi Setup 
int status = WL_IDLE_STATUS;             // the Wi-Fi radio's status
int ledState = LOW;                       //ledState used to set the LED
unsigned long previousMillisInfo = 0;     //will store last time Wi-Fi information was updated
unsigned long previousMillisLED = 0;      // will store the last time LED was updated
const int intervalInfo = 5000;            // interval at which to update the board information

void setup() {
  // Serial port
  Serial.begin(9600);

  // WiFi LED initialization
  pinMode(21, OUTPUT);

  // attempt to connect to Wi-Fi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to network: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.print("Connected to network ");
  Serial.println(ssid);

  // Display
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 14};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = true; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected. Then, you only need to specify 7 segmentPins[]
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);

  // Set display brightness
  sevseg.setBrightness(10);

  // Start sensor
  dht.begin();
}


void loop() {
  // When timer finish
  long current_time = millis();
  if (current_time - prev_time >= sensor_timer){
    
    sevseg.refreshDisplay();
    // Reset timer
    prev_time = current_time;
    
    // Read Sensor
    feels_like = dht.computeHeatIndex(dht.readTemperature(), dht.readHumidity(), false);
    Serial.print("Temp: ");
    Serial.println(feels_like);
    // Check if any read fail
    if (isnan(feels_like)) {
      feels_like = prev_reading;
    }
    else {
      prev_reading = feels_like;
    }
  }
  sevseg.setNumberF(feels_like, 2);
  sevseg.refreshDisplay();
}