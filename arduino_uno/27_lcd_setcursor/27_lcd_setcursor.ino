#include <LiquidCrystal.h>
#define LCD_RS A5
#define LCD_E A4
#define LCD_D4 6
#define LCD_D5 7
#define LCD_D6 8
#define LCD_D7 9

LiquidCrystal lcd(LCD_RS,LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
int counter = 0;
// String word = "Hello World!";

void setup() {
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);    // sets the cursor starting point [argument 1: column number | argument 2: row number]
  lcd.print("Hello");
  lcd.setCursor(0, 2);  
  lcd.print("World!");

}

void loop() {
  lcd.setCursor(7, 1);
  lcd.print(counter);
  counter++;
  delay(500);
}
