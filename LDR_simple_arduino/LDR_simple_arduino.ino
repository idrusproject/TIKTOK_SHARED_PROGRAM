#define ldr A0
#define led 13

int ldrValue ;

void setup() {
  Serial.begin(115200);
  pinMode(ldr, INPUT);
  pinMode(led, OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  ldrValue = analogRead(ldr);
  Serial.println(ldrValue);
  if (ldrValue > 800){
    digitalWrite(led, 0);
  }else{
    digitalWrite(led, 1);
  }
  delay(100);
  // put your main code here, to run repeatedly:

}
