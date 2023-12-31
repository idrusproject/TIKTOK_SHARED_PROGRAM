#include <ArduinoJson.h> // 6.15.2
#include <SoftwareSerial.h>

#define potensio A0

SoftwareSerial mySerial(2, 3); // RX, TX
int count = 0;
unsigned long myTimes ;

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(3, 1);
}

void loop() {
  if (millis() - myTimes > 100UL) {
    count++;
    if (count == 4) {
      count = 0;
    }
    
    // Create a JSON object
    StaticJsonDocument<200> doc;
    doc["data"] = "Hello World!";
    doc["count"] = count;
    doc["potensio"] = analogRead(potensio);

    // Serialize JSON object to a string
    String jsonString;
    serializeJson(doc, jsonString);

    mySerial.println(jsonString);

    Serial.println("Sent JSON : ");
    Serial.println(jsonString);
    myTimes = millis();
  }
  delay(10);
}
