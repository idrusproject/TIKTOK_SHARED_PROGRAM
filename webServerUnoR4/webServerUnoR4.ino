#include "Arduino_LED_Matrix.h"
#include "animation.h"
#include "WiFiS3.h"

#define relay 13

ArduinoLEDMatrix matrix;

char ssid[] = "Max 20A Unfused"; //Enter your WIFI SSID
char pass[] = "bonaparte";   //Enter your WIFI password
int keyIndex = 0;      // your network key index number (needed only for WEP)

String output = "off";
String header;

// Current time
unsigned long currentTime = millis();
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;


int status = WL_IDLE_STATUS;
WiFiServer server(80);

const uint32_t hi[] = {
  0xcdfcdfcc,
  0x4fc4fc4c,
  0xc4cdfcdf,
  66
};

void setup() {
  Serial.begin(115200); // initialize serial communication
  matrix.loadSequence(animation);
  matrix.begin();
  pinMode(relay, OUTPUT); // set the Relay pin mode
  digitalWrite(relay, HIGH);

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Network named: ");
    Serial.println(ssid);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin(); // start the web server on port 80
  printWifiStatus(); // you're connected now, so print out the status
  matrix.play(true);
}


void loop() {
  webServer();
}

void webServer() {
  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the relay on and off
            if (header.indexOf("GET /on") >= 0) {
              output = "on";
              digitalWrite(relay, LOW);
            } else if (header.indexOf("GET /off") >= 0) {
              output = "off";
              digitalWrite(relay, HIGH);
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".on { background-color: #FF0000; border: 5px; color: white; padding: 16px 40px; border-radius: 20px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".off {background-color: #000000;border: 5px; color: white; padding: 16px 40px; border-radius: 20px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}</style></head>");


            // Web Page Heading
            client.println("<body><h1>GoLite Store x Idrus Project</h1>");
            client.println("<body><h2>Internet of Things Dashboard</h2>");
            client.println("<p>Relay " + output + "</p>");
            if (output == "off") {
              client.println("<p><a href=\"/on\"><button class=\"off\">Turn OFF</button></a></p>");
            } else {
              client.println("<p><a href=\"/off\"><button class=\"on\">Turn ON</button></a></p>");
            }

            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("Now open this URL on your browser --> http://");
  Serial.println(ip);
}
