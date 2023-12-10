const int flameSensorPin = 2;  // Flame sensor digital pin
const int buzzerPin = 3;       // Buzzer pin
const int ledPin = 4;          // LED pin

void setup() {
  Serial.begin(9600);
  pinMode(flameSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (!digitalRead(flameSensorPin)) {
    Serial.println("Flame detected!");
    activateAlarm();
  } else {
    Serial.println("No flame detected.");
    deactivateAlarm();
  }
  delay(100);  // Adjust the delay as needed for your application
}

void activateAlarm() {
  digitalWrite(buzzerPin , 1);
  digitalWrite(ledPin, 1);
  delay(100);
  digitalWrite(buzzerPin , 0);
  digitalWrite(ledPin, 0);
  delay(100);
}

void deactivateAlarm() {
  digitalWrite(buzzerPin , 0);
  digitalWrite(ledPin, 0);
}
