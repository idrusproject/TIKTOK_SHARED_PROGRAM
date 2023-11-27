#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 2
#define relay 3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  dht.begin();
  lcd.init();
  lcd.backlight();
  pinMode(relay, OUTPUT);
  digitalWrite(relay, 1);
  lcd.setCursor(0,0);
  lcd.print("Rio_201020100020");
  delay(3000);
  lcd.clear();
  // put your setup code here, to run once:
}

void loop() {
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  lcd.setCursor(0, 0);
  lcd.print("Suhu : ");
  lcd.print(t);
  lcd.print((char)223);
  lcd.print("C");
  lcd.print("    ");
  if (t > 32) {
    digitalWrite(relay, 0);
    lcd.setCursor(0,1);
    lcd.print("Kipas Menyala");
  } else {
    digitalWrite(relay, 1);
    lcd.setCursor(0,1);
    lcd.print("              ");
  }
  delay(100);
  // put your main code here, to run repeatedly:
}
