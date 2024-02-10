#define BLYNK_TEMPLATE_ID "TMPL6WQrsPiTs"
#define BLYNK_TEMPLATE_NAME "Water Flow Meter"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
#define valve 18

#define APP_DEBUG
#define USE_ESP32_DEV_MODULE
#include "BlynkEdgent.h"

volatile int flow_frequency; // Measures flow sensor pulses
// Calculated litres/hour
float vol = 0.0, l_minute;
unsigned char flowsensor = 34; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;
float volume_per_pulse = 0.0;

BLYNK_WRITE(V0) // this command is listening when something is written to V1
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable

  if (pinValue == 1) {
    // do something when button is pressed;
    digitalWrite(valve, 1);
  } else if (pinValue == 0) {
    // do something when button is released;
    digitalWrite(valve, 0);
  }

  Serial.print("V0 button value is: "); // printing value to serial monitor
  Serial.println(pinValue);
}

void flow () // Interrupt function
{
  flow_frequency++;
}

void setup() {
  Serial.begin(115200);
  pinMode(valve, OUTPUT);
  digitalWrite(valve, 0);
  pinMode(flowsensor, INPUT);
  digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up

  attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING); // Setup Interrupt
  currentTime = millis();
  cloopTime = currentTime;
  // Calibrate and set the value of volume_per_pulse here
  volume_per_pulse = 0.004; // Replace with the actual value you've measured
  BlynkEdgent.begin();
  BlynkEdgent.run();
  Blynk.virtualWrite(V1, 0);
  Blynk.virtualWrite(V2, 0);
}

void loop() {

  currentTime = millis();
  // Every second, calculate and print litres/hour
  if (currentTime >= (cloopTime + 1000))
  {
    cloopTime = currentTime; // Updates cloopTime
    if (flow_frequency != 0) {
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      //      l_minute = (bottle_flow_freq * volume_per_pulse * 60);
      l_minute = (flow_frequency / 4.6); // cal_val : 6.6 per datasheet
      Serial.print("Rate: ");
      Serial.print(l_minute);
      Serial.println(" L/M");
      Blynk.virtualWrite(V1, l_minute);

      vol = vol + l_minute / 60;
      Serial.print("Vol:");
      Serial.print(vol);
      Serial.println(" L, ");
      Serial.print("Vol:");
      Serial.print(vol * 1000);
      Serial.println(" mL");
      Blynk.virtualWrite(V2, (vol * 1000));
      flow_frequency = 0; // Reset Counter
    }
    else {
      Blynk.virtualWrite(V1, 0);
      Serial.println("Rate:0 L/M ");
    }
  }
  BlynkEdgent.run();
  delay(10);
}
