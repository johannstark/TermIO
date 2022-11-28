/*******************************************************
TermIO - Indoor temperature and humidity monitor
Source Code for the Wemos D1 Mini Pro (ESP8266)

Written by Juan Esteban Camacho
Made with love in Colombia 🇨🇴
*******************************************************/

// Libraries
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Headers
#include <secret.h>

// Pin definitions
#define SENSOR_PIN 0

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
int ledState = LOW;                       //ledState used to set the LED
unsigned long previousMillisInfo = 0;     //will store last time Wi-Fi information was updated
unsigned long previousMillisLED = 0;      // will store the last time LED was updated
const int intervalInfo = 5000;            // interval at which to update the board information

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

void draw_bitmap(void) {
  display.clearDisplay();

  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(1000);
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
  // Clear the buffer
  display.clearDisplay();
  display.drawPixel(10, 10, SSD1306_WHITE);  // Draw a single pixel in white
  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();

  // WiFi LED initialization
  pinMode(D4, OUTPUT);

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
  // Here, display the value
}