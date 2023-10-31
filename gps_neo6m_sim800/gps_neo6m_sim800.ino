#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <AltSoftSerial.h>

#define led 13

// Create software serial object to communicate with SIM800L
TinyGPSPlus gps;
SoftwareSerial simSerial(2, 3); // 2 = RX, 9 = TX
AltSoftSerial gpsSerial(8, 9); // 8 = RX, 9 = TX

bool smsTrigger = true;
bool gpsValid = false;
String googleMapsURL ;
unsigned long myTimes = 0;

void setup()
{
  Serial.begin(115200);
  simSerial.begin(9600);
  gpsSerial.begin(9600);
  pinMode(led, OUTPUT);
  Serial.println("Initializing...");
  delay(1000);
  simSerial.println("AT"); // Once the handshake test is successful, it will back to OK
  updateSerial();

  simSerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  simSerial.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
  updateSerial();
  while (!gpsValid) {
    while (gpsSerial.available() > 0) {
      if (gps.encode(gpsSerial.read())) {
        gpsInfo();
      }
    }
  }
  sendSmsChunks();
}

void loop()
{
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      gpsInfo();
    }
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    while (true);
  }

  if (millis() - myTimes > 10000UL && gpsValid && smsTrigger) {
    smsTrigger = false;
    sendSms(googleMapsURL);
  }

  updateSerial();
  checkSMS();
  delay(100);
}

void updateSerial()
{
  delay(500);
  //  while (Serial.available())
  //  {
  //    simSerial.write(Serial.read()); // Forward what Serial received to Software Serial Port
  //  }
  while (simSerial.available())
  {
    Serial.write(simSerial.read()); // Forward what Software Serial received to Serial Port
  }
}

void checkSMS()
{
  if (simSerial.available())
  {
    String receivedData = simSerial.readStringUntil('\n');
    if (receivedData.indexOf("lokasi") != -1) // Check if the SMS contains "test"
    {
      sendSmsChunks();
    }
  }
}

void sendSmsChunks()
{
  Serial.println("sendSmsChunks");
  const int maxChunkLength = 153; // Maximum chunk length for SMS
  int startIndex = 0;

  while (startIndex < googleMapsURL.length())
  {
    String chunk = googleMapsURL.substring(startIndex, startIndex + maxChunkLength);
    sendSms(chunk);

    // Increment the start index
    startIndex += maxChunkLength;
  }
}

void sendSms(String message)
{
  simSerial.println("AT+CMGS=\"+6282322631658\"");
  updateSerial();
  delay(1000);
  simSerial.print(message);
  updateSerial();
  simSerial.write(26); // End the message with Ctrl+Z
  updateSerial();
}
