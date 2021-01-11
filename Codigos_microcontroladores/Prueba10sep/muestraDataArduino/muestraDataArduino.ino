// Capturar data y enviar a esp

// Capturar info desde los sensores y enviarla como un json al esp por serial

#include "DHT.h"
#include <ArduinoJson.h> //V5

#define DHTTYPE DHT11
const int DHTPin = 7;

int sensorLightPin = A0;    // pin analogico del sensor de luz
int sensorValue = 0;  // valor inicial
  
DHT dht(DHTPin, DHTTYPE);
void setup() {
    Serial.begin(9600);
    Serial.println("Midiendo...");
  
    dht.begin();
    //mySerial.begin(9600);
}
  
void loop() {
    delay(100000);

    //Crear objeto json
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& data = jsonBuffer.createObject();
  
    //Lectura de los sensores

    data["humidity"] = dht.readHumidity();
    data["temperature"] = dht.readTemperature();

    float lightLevel = analogRead(sensorLightPin);

    Serial.println('lightlevel',lightLevel);


    //FALTA ASIGNAR ESTO
    data["light"] =  -(lightLevel - 1024) / 10.24;
    

    
    //Imprimir la data obtenida como json

    char testJson[200];
    data.printTo(testJson);

    Serial.println(testJson);

    //Enviar los datos al ESP
    //mySerial.write(testJson);

}
