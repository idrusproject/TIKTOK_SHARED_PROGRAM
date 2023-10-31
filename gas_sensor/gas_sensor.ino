#define sensor A0
#define buzzer D5

void setup() {
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  Serial.println(analogRead(sensor));
  if (analogRead(sensor) > 500){
    digitalWrite(buzzer, 1);
    delay(100);
    digitalWrite(buzzer, 0);
    delay(100);
  }
  delay(100);
  // put your main code here, to run repeatedly:

}
