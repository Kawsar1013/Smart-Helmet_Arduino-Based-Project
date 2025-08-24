#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// Define DHT sensor
#define DHTPIN 2       // DHT22 connected to digital pin 2
#define DHTTYPE DHT22  // DHT 22 (AM2302)
DHT dht(DHTPIN, DHTTYPE);

// Define LCD (I2C address 0x27, 16x2 display)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Start LCD
  lcd.init();
  lcd.backlight();

  // Start DHT
  dht.begin();

  // Initial message
  lcd.setCursor(0, 0);
  lcd.print("DHT22 Sensor Test");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read data
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius
  // float temperature = dht.readTemperature(true); // Fahrenheit

  // Check if readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    lcd.setCursor(0, 0);
    lcd.print("Read error!");
    delay(2000);
    return;
  }

  // Display results
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print((char)223); // degree symbol
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Hum:  ");
  lcd.print(humidity, 1);
  lcd.print("%");

  delay(2000); // update every 2 seconds
}
