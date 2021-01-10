#include <ArduinoJson.hpp>
#include <ArduinoJson.h>


//Esta función puede usarse para obtener los datos del sensor
JsonObject& ReturnSerializeObject(StaticJsonBuffer<200> jsonBuffer){
    String json;
    //StaticJsonBuffer<200> jsonBuffer;
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
  Serial.begin(9600);
  Serial.println("------------INICIO PROGRAMA-----------");


  
 

}

void loop()
{
    String stringjson

    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& testjson = ReturnSerializeObject(jsonBuffer);

    doc.printTo(Serial);
    doc.printTo(stringjson);

    Serial.println(stringjson);
}
