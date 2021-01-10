#include <SoftwareSerial.h> //Buscar que hace esta libreria
SoftwareSerial mySerial(2,3); 


void setup() {
    mySerial.begin(9600);
    Serial.begin(9600);
    Serial.write("intentando enviar info...");
}


void loop() {
    mySerial.write("Hello from arduino");
    delay(2000);

    
}
