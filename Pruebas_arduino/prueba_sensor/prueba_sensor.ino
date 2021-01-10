#include "DHT.h"
#define DHTTYPE DHT11 

const int DHTPin = 7;     

DHT dht(DHTPin, DHTTYPE);
  
void setup() {
   Serial.begin(9600);
   Serial.println("Midiendo...");
  
   dht.begin();
}
  
void loop() {
   delay(2000);
  
   float h = dht.readHumidity();
   float t = dht.readTemperature();
  
   if (isnan(h) || isnan(t)) {
      Serial.println("Fallo en la lectura del sensor DHT11");
      return;
   }
  
  
   Serial.print("Humedad relativa: ");
   Serial.print(h);
   Serial.println(" %\t");
   Serial.print("Temperatura: ");
   Serial.print(t);
   Serial.print(" ºC ");
   
}
