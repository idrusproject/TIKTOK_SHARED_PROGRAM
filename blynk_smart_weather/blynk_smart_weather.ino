#include <OneWire.h>
#include <DallasTemperature.h>

// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID           "TMPL6Qjj6eV29"
#define BLYNK_DEVICE_NAME           "Penyiram Tanaman ESP32"
#define BLYNK_AUTH_TOKEN "lEBu58p-XW_n85KbDFDhQx0ZmkA1OXNG"

#define BLYNK_FIRMWARE_VERSION      "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7

#include "BlynkEdgent.h"

#define hum 35
#define oneWireBus 33
#define pump 32
#define buzzer 23

OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);
int humValue;
float tempValue;

BLYNK_WRITE(V3){
  if(param.asInt() == 1){
    Serial.println("pump on");
    digitalWrite(pump,1);  // Set digital pin 2 HIGH
  }
  else{
    Serial.println("pump off");
    digitalWrite(pump,0);  // Set digital pin 2 LOW    
  }
}

void setup()
{
  Serial.begin(115200);
  sensors.begin();
  pinMode(pump, OUTPUT);
  pinMode(buzzer, OUTPUT);
  BlynkEdgent.begin();
  beep(2,100,100);
}

void loop() {
  BlynkEdgent.run();
  getValue();
  Blynk.virtualWrite(V1, tempValue);
  Blynk.virtualWrite(V2, humValue);
}

void getValue () {
  // Read and map humidity sensor value to a 0-100 range
  humValue = map(analogRead(hum), 3500, 0, 0, 100);
  humValue = max(0, humValue);

  sensors.requestTemperatures();
  if (sensors.getTempCByIndex(0) > 0) {
    tempValue = sensors.getTempCByIndex(0);
  }
  Serial.printf("%d:%.2f\n", humValue, tempValue);

}

void beep(int a, int b, int c) {
  for (int i = 0; i < a; i++ ) {
    digitalWrite(buzzer, 1);
    delay(b);
    digitalWrite(buzzer, 0);
    delay(c);
  }
}
