#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); // replace 0x27 with found address

void setup() {
  Wire.begin(22, 20); // SDA, SCL
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello LCD!");
  lcd.setCursor(0,1);
  lcd.print("Testing I2C");
}

void loop() {}