#include <ESP8266WiFi.h>


#define WIFI_SSID "jelvezhernandez"
#define WIFI_PASSWORD "J0Y22ENQ"


void setup() {
  Serial.begin(9600);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  delay(5000);

  Serial.write("Iniciando...");

    
}

void loop() {

  if (WiFi.status() != WL_CONNECTED) {
    Serial.write("Intentando reconectar a wifi: ");
   
    while (WiFi.status() != WL_CONNECTED) {
       WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.write(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }


  // Measure Signal Strength (RSSI) of Wi-Fi connection
  long rssi = WiFi.RSSI();


  //Enviar rssi por conexión serial
  Serial.write(rssi);


  delay(5000);

}
