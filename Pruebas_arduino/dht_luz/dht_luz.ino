#include "DHT.h"

//Sensor DHT
#define DHTTYPE DHT11
const int DHTPin = 7;     
DHT dht(DHTPin, DHTTYPE);

//Sensor de Luz
int sensorPin = A0;    // Conectado al puerto analogico A0


void setup() {
   Serial.begin(9600);
   Serial.println("Midiendo...");
  
   dht.begin();
}
  
void loop() {
   delay(2000); //Lectura de datos cada 2 segundos
  
   float humedad = dht.readHumidity();
   float temperatura = dht.readTemperature();
   float luminosidad = (1024 - analogRead(sensorPin))/1024.0*100.0; //Converte el valor entre 1024 y 0 a un porcentaje entre 0 y 100
  
   if (isnan(humedad) || isnan(temperatura)) {
      Serial.println("Fallo en la lectura del sensor DHT11");
      return;
   }

    
   // Prints de la lectura de datos
   Serial.print("Humedad relativa: ");
   Serial.print(humedad);
   Serial.print(" %\t");
   Serial.print("Temperatura: ");
   Serial.print(temperatura);
   Serial.print(" ºC ");
   Serial.print("Luminosidad");
   Serial.print(luminosidad);
   Serial.println("");

   

   
}
