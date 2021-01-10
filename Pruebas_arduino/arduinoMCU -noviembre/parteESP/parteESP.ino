#include <ESP8266WiFi.h>
#include <NTPClient.h> //https://github.com/taranais/NTPClient
#include <FirebaseArduino.h> //https://github.com/FirebaseExtended/firebase-arduino
#include <WiFiUdp.h>
// Set these to run example.
#define FIREBASE_HOST "test-arduino-d6faa.firebaseio.com"
#define FIREBASE_AUTH "C2PiP3ADqJikd35Rj2nYKCrfR10SkGSObgIhIw5p"
#define WIFI_SSID "jelvezhernandez"
#define WIFI_PASSWORD "J0Y22ENQ"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "0.cl.pool.ntp.org");

void setup() {
    Serial.begin(9600);
    //delay(5000);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while ( WiFi.status() != WL_CONNECTED ) {
        delay ( 500 );
    }

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    timeClient.begin();

}

void loop() {

  timeClient.update();

  String incomingString="";
  boolean stringReady = false;

  while(Serial.available()){
    incomingString = Serial.readString();
    stringReady = true;
  }
  if(stringReady){
    //Serial.print("Recieved String: " + incomingString);

    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& data = jsonBuffer.parseObject(incomingString);

    String dateTime = timeClient.getFormattedDate();
    String timestamp = String(timeClient.getEpochTime());
    //REVISAR QUE LOS DATE QUE SE ENVIAN SIEMPRE SON EL MISMO, AÑADIR UN TIMESTAMP Y FDEJAR LA RUTA COMO
    // SENSOR/TIME/HUM - TEMP - LIGHT
    Firebase.setFloat("sensor5/"+dateTime+"/humidity", data["humidity"]);
    Firebase.setFloat("sensor5/"+dateTime+"/temperature", data["temperature"]);
    Firebase.setFloat("sensor5/"+dateTime+"/light/", data["light"]);
    Firebase.setFloat("sensor5/"+dateTime+"/humiditySuelo/", data["humiditySuelo"]);
    Firebase.setString("sensor5/"+dateTime+"/timestamp/", timestamp);




  }

}
