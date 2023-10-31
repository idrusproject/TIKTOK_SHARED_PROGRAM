#define BLYNK_TEMPLATE_ID "TMPL6a2Q6_Dz4"
#define BLYNK_DEVICE_NAME "DHT11 Monitoring"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
#include "DHT.h"

#define DHTPIN D1
#define APP_DEBUG
#define USE_NODE_MCU_BOARD

#include "BlynkEdgent.h"
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(115200);
  dht.begin();
  delay(100);

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, h);
}
