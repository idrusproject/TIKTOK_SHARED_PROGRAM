#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

volatile int flow_frequency; // Measures flow sensor pulses
// Calculated litres/hour
float vol = 0.0, l_minute;
unsigned char flowsensor = 34; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;
float volume_per_pulse = 0.0;

void flow () // Interrupt function
{
  flow_frequency++;
}

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  pinMode(flowsensor, INPUT);
  digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up

  attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING); // Setup Interrupt
  currentTime = millis();
  cloopTime = currentTime;
  // Calibrate and set the value of volume_per_pulse here
  volume_per_pulse = 0.004; // Replace with the actual value you've measured
  lcd.setCursor(0, 0);
  lcd.print("Water Meter");
}

void loop() {

  currentTime = millis();
  // Every second, calculate and print litres/hour
  if (currentTime >= (cloopTime + 1000))
  {
    cloopTime = currentTime; // Updates cloopTime
    if (flow_frequency != 0){
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      //      l_minute = (flow_frequency / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      l_minute = (flow_frequency * volume_per_pulse * 60);
      Serial.print("Rate: ");
      Serial.print(l_minute);
      Serial.println(" L/M");
      lcd.setCursor(0, 1);
      lcd.print("Rate   :");
      lcd.print(l_minute);
      lcd.print("L/M");

      vol = vol + l_minute / 60;
      Serial.print("Vol:");
      Serial.print(vol);
      Serial.println(" L, ");
      Serial.print("Vol:");
      Serial.print(vol * 1000);
      Serial.println(" mL");
      lcd.setCursor(0, 2);
      lcd.print("Volume :");
      lcd.print(int(vol * 1000));
      lcd.print("mL");
      flow_frequency = 0; // Reset Counter
    }
    else{
      Serial.println("Rate:0 L/M ");
      lcd.setCursor(0, 1);
      lcd.print("Rate   :");
      lcd.print(0);
      lcd.print("L/M     ");
    }
  }
  delay(10);
}
