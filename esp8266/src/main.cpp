/*******************************************************
TermIO - Indoor temperature and humidity monitor
Source Code for the Wemos D1 Mini Pro (ESP8266)

Written by Juan Esteban Camacho
Made with love in Colombia 🇨🇴
*******************************************************/

// Libraries
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Headers
#include <secret.h>

// Pin definitions
#define SENSOR_PIN 14

// Temp Sensor
DHT dht(SENSOR_PIN, DHT11);

// Variable definition
long sensor_timer = 250;
long prev_time = 0;
float prev_reading = 0;
float feels_like = 0;
char res[] = {};

// WiFi Setup 
int status = WL_IDLE_STATUS;             // the Wi-Fi radio's status
unsigned long previousMillisInfo = 0;     //will store last time Wi-Fi information was updated
const int intervalInfo = 5000;            // interval at which to update the board information

// Homebridge Config
WiFiClient client;
HTTPClient hub;
String accessory_id = "";
String hub_url = "http://homebridge.local:51828/";

// Display class
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

void boot_sequence(void) {
  display.clearDisplay();
  delay(2000);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,10);
  display.println(F("Starting up TermIO.."));
  display.setTextSize(1);
  display.println(F("by johannstark"));
  display.display();
  delay(5000);

  display.clearDisplay();
  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(3000);
}

// Push data to Homebridge
void push_data(float data, String reading_type) {
  // Make a GET request to homebridge
  if (reading_type == "temperature") {
    accessory_id = "termio-temperature";
  }
  else if (reading_type == "humidity") {
    accessory_id = "termio-humidity";
  }
  else if (reading_type == "plant") {
    accessory_id = "charlie-brown";
  }
  else {
    Serial.println("[HTTP - Homebridge] Invalid reading type");
    return;
  }
  String endpoint = hub_url+"?accessoryId="+accessory_id+"&value="+String(data);
  if (hub.begin(client, endpoint)) {
    // if it works, get the status code and response
    int status_code = hub.GET();
    Serial.printf("[HTTP - Homebridge] GET %s %d VALUE: %f - ", accessory_id.c_str(), status_code, data);
    Serial.println("response: " + hub.getString());
  }
  else {
    Serial.println("[HTTP - Homebridge] Unable to connect");
  }
}

void setup() {
  // Serial port
  Serial.begin(9600);

  // Display, definitions in the display_functions.h file
  Serial.println("Setting up display");
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  else {
    Serial.println(F("SSD1306 allocation success"));
    boot_sequence();
  }
  // Clear the buffer and set display to default
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // attempt to connect to Wi-Fi network:
  WiFi.mode(WIFI_STA);
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(F("Connecting to WiFi..."));
  display.display();
  while (status != WL_CONNECTED) {
    Serial.println("Attempting to connect to network: "+String(ssid));
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.print("Connected to network ");
  Serial.println(ssid);
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(F("WiFi Connected!"));
  display.display();
  delay(3000);

  // Start sensor
  Serial.println("Starting sensor");
  dht.begin();
}

void loop() {
  // When timer finish
  long current_time = millis();
  if (current_time - prev_time >= sensor_timer){
    
    // Reset timer
    prev_time = current_time;

    // Read Sensors
    float temp_reading = dht.readTemperature();
    int analog_value = analogRead(A0);
    int plant_humidity = map(analog_value, 239, 595, 100, 0);
    
    // Check if any read fail
    if (temp_reading != prev_reading) {
      // If the reading is different, make the reading
      Serial.print("AnalogValue: ");
      Serial.println(analog_value);
      display.clearDisplay();
      display.setCursor(0,0);
      display.setTextSize(2);
      display.print(F("T:")); display.print(temp_reading); display.println(F(" C"));
      display.print(F("Soil: ")); display.print(plant_humidity); display.println(F(" %"));
      display.display();

      // and Push it to Homebridge
      push_data(dht.readTemperature(), "temperature");
      push_data(dht.readHumidity(), "humidity");
      push_data(plant_humidity, "plant");

      // Update previous reading
      prev_reading = temp_reading;
    }
    // Otherwise, do nothing
  }
}