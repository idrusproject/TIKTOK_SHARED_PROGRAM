#define sensor A0
#define buzzer 3
#define led 2

void setup() {
  Serial.begin (115200);
  pinMode (sensor, INPUT);
  pinMode(led, OUTPUT);
  pinMode (buzzer, OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  if (analogRead(sensor) <= 600) {
    digitalWrite(buzzer, 1);
    digitalWrite(led, 1);
    delay(50);
    digitalWrite(buzzer, 0);
    digitalWrite(led, 0);
    delay(80);
  } else {
    digitalWrite(buzzer, 0);
    digitalWrite(led, 0);
  }
  Serial.println(analogRead(sensor));
  delay(100);
  // put your main code here, to run repeatedly:

}
