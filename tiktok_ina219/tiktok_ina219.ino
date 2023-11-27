#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_INA219.h>
Adafruit_INA219 ina219;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(void)
{
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  uint32_t currentFrequency;

  Serial.println("Hello!");
  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) {
      delay(10);
    }
  }
  ina219.setCalibration_16V_400mA();
  Serial.println("Memulai INA219 ...");
  lcd.setCursor(0, 0);
  lcd.print(" DC Power Meter ");
  lcd.setCursor(0, 1);
  lcd.print("  GoLite Store  ");
  delay(2000);
  lcd.clear();
}

void loop(void)
{
  float busvoltage, current_mA = 0;

  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  lcd.setCursor(0, 0);
  lcd.print("Volt : ");
  lcd.print(busvoltage);
  lcd.print("V ");
  lcd.setCursor(0, 1);
  lcd.print("Curr : ");
  lcd.print(current_mA);
  lcd.print("mA   ");
  delay(300);
}
