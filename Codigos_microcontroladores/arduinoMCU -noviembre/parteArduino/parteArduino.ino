
#include <ArduinoJson.h> //V5
#include "DHT.h"
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

#define DHTTYPE DHT11

const int sensorLDR = A1;
const int sensorHum = A2;
const int DHTPin = 4;  

SoftwareSerial mySerial(2,3); 
DHT dht(DHTPin, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);//Direccion de LCD
 
void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  dht.begin();
  lcd.begin(16,2);
}
 
void loop()
{

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();
  
  int valueLDR = 0;
  float light = 0;
  float lightAcum = 0;
  
  
  //Obtener 10 datos de temperatura, para reducir el ruido
  
  for (byte i = 0; i < 10; i = i + 1) {
    valueLDR = analogRead(sensorLDR);
    light = map(valueLDR, 0, 1023, 0, 100); 
    lightAcum = light + lightAcum;
  }

  light = lightAcum/10.0;

  float temperatura = ((int) (dht.readTemperature()*10))/10.0;
  float humedad = ((int) (dht.readHumidity()*10))/10.0;
  int valueHumSuelo = analogRead(sensorHum);

  float humSuelo = map(valueHumSuelo, 260, 455, 100, 0); 
  
  Serial.println("Temperatura: "+String(temperatura)+"°C");
  Serial.println("Luz: "+String(light));
  Serial.println("Humedad: "+String(humedad));
  Serial.println("HumedadSuelo: "+String(humSuelo));

  data["humidity"] = humedad;
  data["temperature"] = temperatura;
  data["light"] = light;
  data["humiditySuelo"] = humSuelo;

  char testJson[200];
  data.printTo(testJson);

  lcd.clear();//Elimina todos los simbolos del LCD
    lcd.setCursor(0,0);//Posiciona la primera letra despues del segmento 5 en linea 1             
    lcd.print("Temp:");

    lcd.setCursor(5,0);
    lcd.print(temperatura,1);

    lcd.setCursor(9,0);
    lcd.print("C Luz:");

    lcd.setCursor(0,1);//Posiciona la primera letra despues del segmento 5 en linea 1             
    lcd.print("Hume:");

    lcd.setCursor(5,1);
    lcd.print(humedad,1);

    lcd.setCursor(9,1);
    lcd.print("% ");

    lcd.setCursor(11,1);
    lcd.print(float(data["light"]),1);

    lcd.setCursor(15,1);
    lcd.print("%");

  //Serial.println(testJson);

  //Enviar los datos al ESP
  mySerial.write(testJson);
  
  delay(10000);
}
