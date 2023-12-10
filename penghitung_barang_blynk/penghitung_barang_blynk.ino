// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID           "TMPL6V2QRCuKZ"
#define BLYNK_DEVICE_NAME           "Penghitung Barang"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_WROVER_BOARD
#include "BlynkEdgent.h"

#define ir 15
int count ;

BLYNK_WRITE(V2){
  if(param.asInt() == 1){
    count = 0;
    Blynk.virtualWrite(V1, count);
  }
  else{
  }
}

void setup(){
  Serial.begin(115200);
  delay(100);
  pinMode(ir, INPUT_PULLUP);
  BlynkEdgent.begin();
}

void loop() {
  if (!digitalRead(ir)){
    while(!digitalRead(ir)){
      delay(10);
    }
    count++;
    Blynk.virtualWrite(V1, count);
  }
  BlynkEdgent.run();
}
