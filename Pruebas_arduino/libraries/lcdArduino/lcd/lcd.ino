#include <Wire.h>
#include <LiquidCrystal_I2C.h>
char array1[] = " INOVATRIX GUYS";  // CHANGE THIS AS PER YOUR NEED 
char array2[] = " LIKE,SUBSCRIBE";  // CHANGE THIS AS PER YOUR NEED 
LiquidCrystal_I2C lcd(0x27, 16, 2); // CHANGE THE 0X3F ADDRESS TO YOUR SCREEN ADDRESS IF NEEDED
void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.print(array1);
  lcd.setCursor(0,2);
  lcd.print(array2);
}
void loop()
{}
