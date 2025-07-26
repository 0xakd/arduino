#include <LiquidCrystal.h>
#define LCD_RS A5
#define LCD_E A4
#define LCD_D4 6
#define LCD_D5 7
#define LCD_D6 8
#define LCD_D7 9

int currentRow = 0;

LiquidCrystal lcd(LCD_RS,LCD_E,LCD_D4,LCD_D5,LCD_D6,LCD_D7);


void displayTextOnLCD(String userText){
  if(userText.length() > 16){
    userText = "Text too Long!";
  }

  for(int i = userText.length(); i < 16; i++){
    userText += " "; 
  }
  
  lcd.setCursor(0, currentRow);
  lcd.print(userText);

  if(currentRow == 0){
    currentRow = 1;
  }else{
    currentRow = 0;
  }
}


void setup() {
  Serial.begin(115200);
  Serial.setTimeout(10);
  lcd.begin(16, 2);
}

void loop() {
  if(Serial.available() > 0){
    String str = Serial.readString();
    displayTextOnLCD(str);
  }
}

