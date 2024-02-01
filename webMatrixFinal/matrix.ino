#include <WiFiS3.h>
#include "Arduino_LED_Matrix.h"
#include "webcontent.h"
#include "frameFunctions.h"


ArduinoLEDMatrix matrix;

const char ssid[] = "wilsonServer";
const char pass[] = "password123";
int keyIndex = 0;

int status = WL_IDLE_STATUS;

int row = 0;
int column = 0;

WiFiServer server(80);

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Access Point Web Server");

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true)
      ;
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // by default the local IP address will be 192.168.4.1
  // you can override it with the following:

  // print the network name (SSID);
  Serial.print("Creating access point named: ");
  Serial.println(ssid);

  // Create open network. Change this line if you want to create an WEP network:
  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    // don't continue
    while (true)
      ;
  }

  // wait 10 seconds for connection:
  delay(10000);

  // start the web server on port 80
  server.begin();

  // you're connected now, so print out the status
  printWiFiStatus();
  matrix.begin();
}



void loop() {
  // compare the previous status to the current status
  if (status != WiFi.status()) {
    // it has changed update the variable
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      // a device has connected to the AP
      Serial.println("Device connected to AP");
    } else {
      // a device has disconnected from the AP, and we are back in listening mode
      Serial.println("Device disconnected from AP");
    }
  }

  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    // read the first line of HTTP request header
    String HTTP_req = "";
    while (client.connected()) {
      if (client.available()) {
        Serial.println("New HTTP Request");
        HTTP_req = client.readStringUntil('\n');  // read the first line of HTTP request
        Serial.print("<< ");
        Serial.println(HTTP_req);  // print HTTP request to Serial Monitor
        break;
      }
    }

    // read the remaining lines of HTTP request header
    while (client.connected()) {
      if (client.available()) {
        String HTTP_header = client.readStringUntil('\n');  // read the header line of HTTP request

        if (HTTP_header.equals("\r"))  // the end of HTTP request
          break;

        Serial.print("<< ");
        Serial.println(HTTP_header);  // print HTTP request to Serial Monitor
      }
    }

    if (HTTP_req.indexOf("GET") == 0) {  // check if request method is GET
      // expected header is one of the following:
      // - GET ?/message= "user message"
      if (HTTP_req.indexOf("message=") > -1) {         // check the path
        int pos_1 = HTTP_req.indexOf("message=") + 8;  // 8 is the lengh of "message="
        int pos_2 = HTTP_req.indexOf(" ", pos_1);
        String message = HTTP_req.substring(pos_1, pos_2);
        Serial.print("message: ");
        Serial.println(message);

        //processes message to frame data
        if(message.length() == 2){

          //for debugging
          Serial.println("valid input"); 
          Serial.println(message[0]);
          Serial.println(message[1]);

          //converts row from ascii value to int value
          row = message[1] - 49;
          //converts column from ascii value to int value and handles upper/lowercase
          column = letterToColumn(message[0]);

          //flips assigned pixel and writes to LED
          flipPixel(row,column);
          matrix.renderBitmap(frame, 8, 12);
        }
      }
    }

    // send the HTTP response
    // send the HTTP response header
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");  // the connection will be closed after completion of the response
    client.println();                     // the separator between HTTP header and body
                                          // send the HTTP response body
    String html = String(HTML_CONTENT);
    client.println(html);
    client.flush();

    // give the web browser time to receive the data
    delay(10);

    // close the connection:
    client.stop();
  }
}
