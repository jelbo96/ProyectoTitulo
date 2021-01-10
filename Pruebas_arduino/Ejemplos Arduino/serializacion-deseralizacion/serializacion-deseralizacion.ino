// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>

void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  while (!Serial) continue;

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  //Ver como convertir un JsonObject a JsonVariant

  root["sensor"] = "gps";
  root["time"] = 1351824120;

  Serial.println("------------------------Imprimiendo como json----------------\n");
  root.printTo(Serial);
  
  Serial.println();
  Serial.println("------------------------Imprimiendo como json pretty----------------\n");
  root.prettyPrintTo(Serial);

  String testJson;
  root.printTo(testJson);

  Serial.println();
  Serial.println("------------------------Imprimiendo como string----------------");
  Serial.println(testJson);


  //Aca tengo que lograr modificar el json para añadir mas cosas
  StaticJsonBuffer<200> jsonBuffer2;
  JsonObject& root2 = jsonBuffer2.parseObject(testJson);

  if(!root2.success()){
    Serial.println("ERROR");
    return;
  }

  String sensordeserializated = root2["sensor"];
  float timedeserializated = root2["time"];

  Serial.println();
  Serial.println("------------------DESERIALIZADO----------");
  Serial.println("sensor: "+sensordeserializated+" time: "+timedeserializated);



  //Enviar un json desde arduino a esp -> pero desde esp hacer push int a un path que se defina segun la hora/fecha
}

void loop() {
  // not used in this example
}
