#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

#define lock 11
String qrKey = "idrusproject";
String incomingData;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(lock, OUTPUT);
  digitalWrite(lock, 1);
  Serial.println("System ready to use, with key: " + qrKey);
}

void loop() {
  if (mySerial.available()) {
    Serial.println("Incoming Data: ");
    incomingData = mySerial.readString();
    incomingData.trim();
    Serial.println(incomingData);
    Serial.println("Data Length: " + String(incomingData.length()));
    if (incomingData.equals(qrKey)) {
      digitalWrite(lock, 0);
      delay(2000);
      digitalWrite(lock, 1);
    }
  }

  if (Serial.available()) {
    String inputData = Serial.readString();
    mySerial.print(inputData);
  }
  delay(1000);
}
