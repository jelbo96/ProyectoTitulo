#include <ArduinoJson.hpp>
#include <ArduinoJson.h>

//Esta función puede usarse para obtener los datos del sensor
String ReturnSerializeObject(){
  
    String json;
    StaticJsonDocument<300> doc;
    doc["humedad"] = 40;
    doc["temperatura"] = 10;
    doc["luminosidad"] = 50;
    
    serializeJson(doc, json);
    
    Serial.println(json);
    return json;
}

//Esta función puede usarse para almacenar la info desde el node
//añadir la fecha/hora y subir el json a firebase
void DeserializeJsonObject(String json){
  
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
    
}


void setup()
{
    Serial.begin(115200);

    Serial.println("===== Object Example =====");
    Serial.println("-- Serialize --");
    String testjson = ReturnSerializeObject();
    Serial.println();
    Serial.println("-- Deserialize --");
    DeserializeJsonObject(testjson);



    Serial.println("FIN PROGRAMA -----------------------");
}

void loop()
{
}
