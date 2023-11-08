#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10  // Slave Select Pin (SS)
#define RST_PIN 9  // Reset Pin
#define RELAY_PIN 8  // Relay Control Pin (connected to D8)
#define buzzer 7 // Active HIGH Buzzer Pin (connected to D7)
#define greenLed 6 // Active HIGH Green LED Pin (connected to D6)
#define redLed 5 // Active HIGH Red LED Pin (connected to D5)
#define exitBtn 2 // Active LOW Exit Button Pin (connected to D5)

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

unsigned long previousMillis = 0;
const unsigned long relayOpenTime = 3000; // 3 seconds

// Define an array of authorized card UIDs
String authorizedCards[] = {
  "42 85 0B 24",  // Add more UIDs as needed
  "81 69 B8 89",  // Second authorized card UID
  "E7 F9 0D 53"   // Third authorized card UID
};

void setup() {
  Serial.begin(115200);
  SPI.begin();   // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(exitBtn, INPUT_PULLUP);

  digitalWrite(RELAY_PIN, 0); // Initialize the relay in the closed state
  digitalWrite(buzzer, 1);
  digitalWrite(redLed, 1);
  digitalWrite(greenLed, 1);
  delay(500);
  digitalWrite(buzzer, 0);
  digitalWrite(redLed, 0);
  digitalWrite(greenLed, 0);
  Serial.println("System Ready To Use");
}

void loop() {
  if (!digitalRead(exitBtn)) {
    while (!digitalRead(exitBtn)) {
      delay(100);
    }
    Serial.println("Exit With Exit Button");
    beep(2, 100, 100);
    digitalWrite(greenLed, 1);
    digitalWrite(RELAY_PIN, 1);
    delay(3000);
    digitalWrite(RELAY_PIN, 0);
    digitalWrite(greenLed, 0);
  }
  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Print UID of the card
    Serial.print("UID tag :");
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    content.toUpperCase();
    content.trim();

    // Check if the scanned card UID is in the authorizedCards array
    bool isAuthorized = false;
    for (int i = 0; i < sizeof(authorizedCards) / sizeof(authorizedCards[0]); i++) {
      if (content == authorizedCards[i]) {
        isAuthorized = true;
        break;
      }
    }

    Serial.print("Message : ");
    if (isAuthorized) {
      Serial.println("Authorized access");
      beep(2, 100, 100);
      digitalWrite(greenLed, 1);
      digitalWrite(RELAY_PIN, 1);
      delay(3000);
      digitalWrite(RELAY_PIN, 0);
      digitalWrite(greenLed, 0);
    } else {
      Serial.println("Access denied");
      digitalWrite(redLed, 1);
      beep(1, 1000, 1000);
      digitalWrite(redLed, 0);
    }
    delay(100); // Delay a bit between readings to avoid card flickering
  }
  delay(250);
}

void beep(int a, int b, int c) {
  for (int i = 0; i < a; i++ ) {
    digitalWrite(buzzer, 1);
    delay(b);
    digitalWrite(buzzer, 0);
    delay(c);
  }
}
