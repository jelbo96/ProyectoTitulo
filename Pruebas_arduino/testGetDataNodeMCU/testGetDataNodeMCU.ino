#include "DHT.h"
#include <ArduinoJson.h> //V5
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h> //https://github.com/taranais/NTPClient
#include <FirebaseArduino.h> //https://github.com/FirebaseExtended/firebase-arduino
#include <WiFiUdp.h>
#include <LiquidCrystal_I2C.h>


// Set these to run example.
#define FIREBASE_HOST "test-arduino-d6faa.firebaseio.com"
#define FIREBASE_AUTH "C2PiP3ADqJikd35Rj2nYKCrfR10SkGSObgIhIw5p"
#define WIFI_SSID "mio"
#define WIFI_PASSWORD "asdfghjk"
 
#define DHTTYPE DHT11
// Define Pins
const int DHTPin = D4;  
const int sensorLightPin = A0;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "0.cl.pool.ntp.org");
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);//Direccion de LCD

DHT dht(DHTPin, DHTTYPE);

void setup() {
    Serial.begin(115200);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    lcd.begin(16,2);
    while ( WiFi.status() != WL_CONNECTED ) {
        delay ( 500 );
        lcd.setCursor(0,0);//Posiciona la primera letra despues del segmento 5 en linea 1             
        lcd.print("Conectando");
    }

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    timeClient.begin();

    
    Serial.println("Midiendo...");
    dht.begin();
    
}

void loop(){
  if(WiFi.status() == WL_CONNECTED){
    timeClient.update();
    
    //Crear objeto json
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& data = jsonBuffer.createObject();
  
    //Lectura de los sensores

    //data["humidity"] = dht.readHumidity();
    //ta["temperature"] = dht.readTemperature();
    
    float lightLevel = analogRead(sensorLightPin);
    data["light"] =  -(lightLevel - 1024) / 10.24;


    float temperatura = ((int) (dht.readTemperature()*10))/10.0;
    float humedad = ((int) (dht.readHumidity()*10))/10.0;
    

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


    
    //Imprimir la data obtenida como json

    char testJson[200];
    data.printTo(testJson);

    Serial.println(testJson);

    String dateTime = timeClient.getFormattedDate();
    String timestamp = String(timeClient.getEpochTime());

    //REVISAR QUE LOS DATE QUE SE ENVIAN SIEMPRE SON EL MISMO, AÑADIR UN TIMESTAMP Y FDEJAR LA RUTA COMO
    // SENSOR/TIME/HUM - TEMP - LIGHT
    Firebase.setFloat("sensor4/"+dateTime+"/humidity", humedad);
    Firebase.setFloat("sensor4/"+dateTime+"/temperature", temperatura);
    Firebase.setFloat("sensor4/"+dateTime+"/light/", data["light"]);
    Firebase.setString("sensor4/"+dateTime+"/timestamp/", timestamp);
  }
  else{
    Serial.println("Reconecting ....");
    
    lcd.setCursor(0,0);//Posiciona la primera letra despues del segmento 5 en linea 1             
    lcd.print("EW");
    WiFi.reconnect();
  }
    
    
    delay(10000);
}

// Mapear rangos https://www.arduino.cc/reference/en/language/functions/math/map/
