#include <SoftwareSerial.h> //Buscar que hace esta libreria
SoftwareSerial mySerial(2,3); 

void setup() {
  Serial.begin(115200);
  Serial.print("Hello World from ESP");
  mySerial.begin(115200);
  delay(5000);
}

void loop() {
  String incomingString="";
  boolean stringReady = false;

  while(mySerial.available()){
    incomingString = mySerial.readString();
    stringReady = true;
  }
  if(stringReady){
    Serial.print("Recieved String: " + incomingString);
  }

}
