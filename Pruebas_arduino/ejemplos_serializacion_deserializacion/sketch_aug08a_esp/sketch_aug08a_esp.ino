#include <ArduinoJson.hpp>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
// Set these to run example.
#define FIREBASE_HOST "test-arduino-d6faa.firebaseio.com"
#define FIREBASE_AUTH "C2PiP3ADqJikd35Rj2nYKCrfR10SkGSObgIhIw5p"
#define WIFI_SSID "jelvezhernandez"
#define WIFI_PASSWORD "J0Y22ENQ"


//Esta función puede usarse para obtener los datos del sensor
JsonObject& ReturnSerializeObject(){
    String json;
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& doc = jsonBuffer.createObject();

    doc["humedad"] = 40;
    doc["temperatura"] = 10;
    doc["luminosidad"] = 50;
  
    //doc.printTo(json);

    //Serial.println(json);
    return doc;
    
}

//Esta función puede usarse para almacenar la info desde el node
//añadir la fecha/hora y subir el json a firebase
void DeserializeJsonObject(String json){
    /*
    StaticJsonDocument<300> doc;
    DeserializationError error = deserializeJson(doc, json);
    if (error) { return; }

    float humedad = doc["humedad"];
    float temperatura = doc["temperatura"];
    float luminosidad = doc["luminosidad"];
    //Aca en el node deberia añadir la fecha/hora de la medición

    Serial.println(humedad);
    Serial.println(temperatura);
    Serial.println(luminosidad);
    */    
}


void setup()
{
  /*
    Serial.begin(115200);

    Serial.println("===== Object Example =====");
    Serial.println("-- Serialize --");
    
    Serial.println();
    Serial.println("-- Deserialize --");
    //DeserializeJsonObject(testjson);

*/

  Serial.println("FIN PROGRAMA -----------------------");


  Serial.begin(9600);
  delay(5000);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop()
{
    JsonObject& testjson = ReturnSerializeObject();

    Firebase.push("medition", testjson);
}
