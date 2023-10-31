#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C address
const int irSensorPin = 2;
int objectCount = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();                // Initialize the LCD
  lcd.backlight();           // Turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("Object Count:");
  lcd.setCursor(0, 1);
  pinMode(irSensorPin, INPUT);
}

void loop() {
  // Read the IR sensor
  if (digitalRead(irSensorPin)){
    while(digitalRead(irSensorPin)){
      delay(10);
    }
    objectCount++;
    lcd.setCursor(0, 1);
    lcd.print(objectCount);
    Serial.println("Object detected.");
  }
  delay(100);
}
