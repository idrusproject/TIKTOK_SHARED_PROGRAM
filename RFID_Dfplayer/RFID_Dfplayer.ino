/*
   MP3 List :
   - 0001 : Akses diterima
   - 0002 : Akses ditolak
*/

#include <SPI.h>
#include <MFRC522.h>
#include <DFPlayer_Mini_Mp3.h>

#define RST_PIN         9        // Define the RST_PIN
#define SS_PIN          10       // Define the SS_PIN

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

SoftwareSerial mySerial(2, 3); //RX, TX


void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");

  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card

  mySerial.begin (9600);
  mp3_set_serial (mySerial);
  mp3_set_volume (90);

  Serial.println("System is ready .");

  // put your setup code here, to run once:

}

void loop() {
  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Show card UID on serial monitor
    Serial.print("UID Tag : ");
    String content = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println(content);

    // Check if the scanned UID matches the allowed UID
    if (content.equals("d3ab6bad")) {
      Serial.println("Access Granted!");
      mp3_play(1);
      delay(2000);
    } else {
      Serial.println("Access Denied!");
      mp3_play(2);
      delay(2000);
    }

    mfrc522.PICC_HaltA();
  }
  // put your main code here, to run repeatedly:

}
