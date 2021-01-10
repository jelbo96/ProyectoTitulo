#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3); //RX, TX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  String IncomingString="";
  boolean StringReady = false;

  while (mySerial.available()){
    IncomingString=mySerial.readString();
    StringReady= true;
  }

  if(StringReady){
    Serial.println("Recieved String: " + IncomingString);
  }
}
