/*Ejemplo para controlar un LCD con un modulo Serial
Instrucciones:
VCC del modulo: 5v 
GND del modulo: GND
SCL del modulo (varia dependiendo de la placa Arduino) 
SDA del modulo (varia dependiendo de la placa Arduino) 
*/
#include <Wire.h>                 
#include <LiquidCrystal_I2C.h>//Recuerda descargar la libreria en electrocrea.com    
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);//Direccion de LCD
void setup()   { 
lcd.begin(16,2);// Indicamos medidas de LCD        
}
void loop() {
lcd.clear();//Elimina todos los simbolos del LCD
lcd.setCursor(5,1);//Posiciona la primera letra despues del segmento 5 en linea 1             
lcd.print("Altronics.cl");
delay (2000);//Dura 2 segundos
lcd.clear();
lcd.setCursor(6,2);//Posiciona la primera letra despues del segmento 6 en linea 2            
lcd.print("Visitanos!");
delay (1000);//Dura 1 segundo  
 }
