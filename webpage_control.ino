#include <ESP8266WiFi.h>
#include <Servo.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

WiFiServer server(80);
Servo myservo;
const int servoPin = D4;

void setup() {
  Serial.begin(115200);
  myservo.attach(servoPin);
  myservo.write(0); // Initial position

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.println("Connected!");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  while (!client.available()) delay(1);
  String request = client.readStringUntil('\r');
  client.flush();

  if (request.indexOf("/unlock") != -1) {
    myservo.write(90);  // Unlock
    delay(2000);
    myservo.write(0);   // Lock back
  }

  client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
  client.print("<!DOCTYPE html><html><body><h1>Smart Delivery</h1>");
  client.print("<button onclick=\"location.href='/unlock'\">Unlock Box</button>");
  client.print("</body></html>");
}
