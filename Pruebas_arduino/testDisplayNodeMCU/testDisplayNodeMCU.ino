#include <LiquidCrystal_I2C.h>

// Construct an LCD object and pass it the 
// I2C address, width (in characters) and
// height (in characters). Depending on the
// Actual device, the IC2 address may change.

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);//Direccion de LCD

void setup()   { 
lcd.begin(16,2);// Indicamos medidas de LCD        
}
void loop() {
lcd.clear();//Elimina todos los simbolos del LCD
lcd.setCursor(0,0);//Posiciona la primera letra despues del segmento 5 en linea 1             
lcd.print("Temp:20,2C Luz:");

lcd.setCursor(0,2);//Posiciona la primera letra despues del segmento 5 en linea 1             
lcd.print("Hume:70,5% 15,2%");


delay (2000);//Dura 2 segundos

 }
