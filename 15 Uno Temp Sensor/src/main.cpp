// /**
//  *
//  *****************************************************************
//  * IOT Challenges - https://instagram.com/iotchallenges          *
//  *****************************************************************
//  * Evandro Fruhauf                                               *
//  *  GitHub - https://github.com/evandrodp                        *
//  *  LinkedIn - http://linkedin.com/in/evandrofruhauf             *
//  *****************************************************************
//  * This code can contain parts from other open-sources projects, *
//  * whenever possible it will be quoted.                          *
//  *****************************************************************
//  *
//  * Temperature and Humidity
//  *
//  * Challenge: Read the Temperature and Humidity and show on the LCD
//  *
//  * This source is using the LiquidCrystal library by Malpartida. (Installed by PlatformIO)
//  * This source is using the Adafruit_Sensor and Adafruit DHT library. (Installed by PlatformIO)
//  *
//  * This code is an example from Adafruit library.
//  *
//   **/
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// define the lcd ports
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Digital pin connected to the DHT sensor
#define DHTPIN 7
#define DHTTYPE DHT11
uint32_t delayMS;

DHT_Unified dht(DHTPIN, DHTTYPE);

// define the methods
void textWelcome();
void showMeasurements();

void setup() {
  lcd.begin(16,2); // initialise the lcd
  dht.begin(); // initialise the sensor
  // Set delay between sensor readings based on sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
  textWelcome();
  delay(2000);
}

void loop() {
  showMeasurements();
  delay(delayMS); // Delay between measurementss
}

void textWelcome() {
  lcd.home(); // go home 0, 0
  lcd.print(" IOT CHALLENGES");
  lcd.setCursor ( 0, 1 );
  lcd.print ("Temp & Humidity");
}

void showMeasurements() {
  sensors_event_t event;
  lcd.home(); // change the first line
  // Get temperature event and print its value.
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    lcd.print("TEMP: Fail      ");
  } else {
    lcd.print("TEMP: ");
    lcd.print(event.temperature);
    lcd.print(" C    ");
  }
  lcd.setCursor ( 0, 1 ); // change the second line
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    lcd.print("HUMIDITY: Fail  ");
  }
  else {
    lcd.print("HUMIDITY: ");
    lcd.print(event.relative_humidity);
    lcd.print("%");
  }
}
