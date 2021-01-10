
#include <ArduinoJson.h> //V5
#include <SoftwareSerial.h>

const int sensorLM35= A3;
const int sensorLDR = A1;
const int sensorHum = A2;

SoftwareSerial mySerial(2,3); 
 
void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
}
 
void loop()
{

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();
  
  int valueTemp = analogRead(sensorLM35);
  int valueLDR = analogRead(sensorLDR);
  int valueHum = analogRead(sensorHum);

  float tempC = (5.0 * valueTemp * 100.0)/1024.0;
  float hum = map(valueHum, 260, 455, 100, 0); 
  
  Serial.println("Temperatura: "+String(tempC)+"°C");
  Serial.println("Luz: "+String(valueLDR));
  Serial.println("Humedad: "+String(hum));

  data["humidity"] = hum;
  data["temperature"] = tempC;
  data["light"] = valueLDR

  char testJson[200];
  data.printTo(testJson);

  Serial.println(testJson);

  //Enviar los datos al ESP
  mySerial.write(testJson);
  
  delay(10000);
}
