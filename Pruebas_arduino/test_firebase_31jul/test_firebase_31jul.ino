
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
// Set these to run example.
#define FIREBASE_HOST "test-arduino-d6faa.firebaseio.com"
#define FIREBASE_AUTH "C2PiP3ADqJikd35Rj2nYKCrfR10SkGSObgIhIw5p"
#define WIFI_SSID "jelvezhernandez"
#define WIFI_PASSWORD "J0Y22ENQ"


void setup() {
  Serial.begin(9600);
  delay(5000);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    /* Serial.print("connecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP()); */
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  String incomingString="";
  boolean stringReady = false;

  while(Serial.available()){
    incomingString = Serial.readString();
    stringReady = true;
  }
  if(stringReady){
    Serial.print("Recieved String: " + incomingString);
    Firebase.setString("message", incomingString);
  }

}
