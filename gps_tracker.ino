#include <SoftwareSerial.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;
SoftwareSerial ss(4, 3); // RX, TX (connect GPS TX to pin 4, RX to 3)

void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  Serial.println("GPS tracking started...");
}

void loop() {
  while (ss.available() > 0) {
    gps.encode(ss.read());
    if (gps.location.isUpdated()) {
      Serial.print("Latitude: ");
      Serial.println(gps.location.lat(), 6);
      Serial.print("Longitude: ");
      Serial.println(gps.location.lng(), 6);
    }
  }
}
