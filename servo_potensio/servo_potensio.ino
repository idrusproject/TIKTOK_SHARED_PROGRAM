#include <Servo.h>

const int servoPin = 3;
const int potPin = A0;

Servo myServo;

void setup() {
  myServo.attach(servoPin);
}

void loop() {
  int potValue = analogRead(potPin);

  int angle = map(potValue, 0, 1023, 0, 180);
  myServo.write(angle);
  
  delay(15);
}
