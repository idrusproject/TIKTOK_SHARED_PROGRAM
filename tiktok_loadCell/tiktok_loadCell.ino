#include "HX711.h"
#include <Wire.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
#define btn 12

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

HX711 scale;
int reading;
int lastReading;
//REPLACE WITH YOUR CALIBRATION FACTOR
#define CALIBRATION_FACTOR 840.592

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  Serial.println("Initializing the scale");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  scale.set_scale(CALIBRATION_FACTOR);   // this value is obtained by calibrating the scale with known weights
  scale.tare();               // reset the scale to 0
  pinMode (btn, INPUT_PULLUP);
  lcd.setCursor(0,0);
  lcd.print("Berat : ");
}

void loop() {

  if (digitalRead(btn) == 0) {
    while (digitalRead(btn) == 0) {
      Serial.print("tare...");
      scale.tare();
    }
  }

  if (scale.wait_ready_timeout(200)) {
    reading = round(scale.get_units());
    Serial.print("Weight: ");
    Serial.println(reading);
    if (reading != lastReading) {
      Serial.print("Weights: ");
      Serial.println(reading);
      lcd.setCursor(8,0);
      lcd.print(reading);
      lcd.print("gr");
      lcd.print("     ");
    }
    lastReading = reading;
  }
  else {
    Serial.println("HX711 not found.");
  }
}
