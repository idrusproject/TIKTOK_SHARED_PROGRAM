#include <WiFi.h>
#include <PubSubClient.h>

// WiFi Credential
const char *ssid = "idrussepti";
const char *password = "idrussepti";

// MQTT Credential
const char *mqtt_broker = "broker.hivemq.com";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

#define trigPin 33
#define echoPin 32
long duration, distance;

// MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// Task for GPS Dual Core
TaskHandle_t Task0;

void setup()
{
  Serial.begin(115200);
  wifiSetup();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
    mqttTask,   /* Task function. */
    "Task0",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &Task0,      /* Task handle to keep track of created task */
    1);          /* pin task to core 0 */
  delay(500);
}

// Network Task
void mqttTask( void * pvParameters ) {
  while (1) {
    Serial.print("Network Task running on core ");
    Serial.println(xPortGetCoreID());
    checkConnection();
    client.publish("esp32/distanceidrus24", (String(distance)+" CM").c_str());
    client.loop();
    delay(100);
  }
}

void loop() {
  Serial.print("Main Task running on core ");
  Serial.println(xPortGetCoreID());
  getDistance();
  delay(100);
}

void getDistance() {
  duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  delay(50);
  Serial.println(distance);
}
