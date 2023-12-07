#define ir 2
#define water 3

void setup() {
  Serial.begin(115200);
  pinMode(ir, INPUT);
  pinMode(water, OUTPUT);
  digitalWrite(water, 1);
  Serial.println("System Ready To Use");
  // put your setup code here, to run once:
}

void loop() {
  Serial.println(digitalRead(ir));
  if (!digitalRead(ir)){
    delay(50);
    digitalWrite(water, 0);
    delay(500);
    digitalWrite(water, 1);
    delay(50);
    while(!digitalRead(ir)){
      delay(10);
    }
    digitalWrite(water, 0);
    delay(500);
    digitalWrite(water, 1);
    delay(50);
  }
  delay(100);
  // put your main code here, to run repeatedly:
}
