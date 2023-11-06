#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// WiFi Credential
const char *ssid = "Max 20A Unfused";
const char *password = "bonaparte";

// MQTT Credential
const char *mqtt_broker = "broker.hivemq.com";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

float temp = 0;
String tempState ;

#define oneWireBus 25
#define greenLed 33
#define redLed 32

OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

// MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// Task for GPS Dual Core
TaskHandle_t Task0;

void setup()
{
  Serial.begin(115200);
  wifiSetup();
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
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
    client.publish("esp32/ds18b20tempidrus24", String(temp).c_str());
    client.publish("esp32/tempstateidrus24", String(tempState).c_str());
    client.loop();
    delay(1000);
  }
}

void loop() {
  Serial.print("Main Task running on core ");
  Serial.println(xPortGetCoreID());
  getTemp();
  delay(100);
}

void getTemp() {
  sensors.requestTemperatures();
  if (sensors.getTempCByIndex(0) > 0) {
    temp = sensors.getTempCByIndex(0);
    if (temp > 35){
      tempState = "SUHU PANAS";
      digitalWrite(greenLed, 0);
      digitalWrite(redLed, 1);
      delay(200);
      digitalWrite(redLed, 0);
      delay(200);
    }else {
      tempState = "SUHU NORMAL";
      digitalWrite(greenLed, 1);
    }
  }
}
