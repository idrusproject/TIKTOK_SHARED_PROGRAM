#include <ArduinoJson.h> // 6.15.2
#include <ESP32Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int leds[] = {26, 25, 33, 32};
Servo myservo;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);  // RX pin, TX pin for Serial2
  lcd.init();
  lcd.backlight();
  for (int ledPin : leds) {
    pinMode(ledPin, OUTPUT);
  }
  // Turn off all LEDs
  for (int ledPin : leds) {
    digitalWrite(ledPin, 0);
  }

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(13, 500, 2400); // attaches the servo on pin 18 to the servo object
  // using default min/max of 1000us and 2000us
  // different servos may require different min/max settings
  // for an accurate 0 to 180 sweep

  Serial.println("Project Ready To Use");
}

void loop() {
  // Check if data is available on Serial2
  if (Serial2.available()) {
    // Read the data from Serial2
    String jsonString = Serial2.readStringUntil('\n');

    // Print the received JSON string to Serial (for monitoring)
    Serial.println("Received JSON : ");
    Serial.println(jsonString);

    // Parse the JSON data
    StaticJsonDocument<1023> doc;
    DeserializationError error = deserializeJson(doc, jsonString);

    // Check for parsing errors
    if (error) {
      Serial.print(F("JSON Parsing Error: "));
      Serial.println(error.c_str());
      return;
    }

    // Access the parsed data
    const char* value1 = doc["data"];
    int count = doc["count"];
    int potensio = doc["potensio"];

    // Turn off all LEDs
    for (int ledPin : leds) {
      digitalWrite(ledPin, 0);
    }

    // Turn on the specific LED based on value2
    if (count >= 0 && count <= 3) {
      digitalWrite(leds[count], 1);
    }
    lcd.setCursor(0, 0);
    lcd.print("Data 1:");
    lcd.print(value1);
    lcd.setCursor(0, 1);
    lcd.print("Data 2:");
    lcd.print(count);
    lcd.setCursor(0, 2);
    lcd.print("Data 3:");
    lcd.print(potensio);


    // Control the servo based on the potentiometer value
    int servoAngle = map(potensio, 0, 1023, 0, 180);  // Map potensio value to servo angle (0 to 180 degrees)
    myservo.write(servoAngle);  // Set the servo position

  }
  delay(100);
}
