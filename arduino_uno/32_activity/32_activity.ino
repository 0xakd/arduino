#include <IRremote.h>
#include <LiquidCrystal.h>

// components constants 
#define IR_RECEIVER 5
#define LED1 10
#define LED2 11
#define LED3 12


// IR Remote Buttons constants  
#define REMOTE_0 22
#define REMOTE_1 12
#define REMOTE_2 24
#define REMOTE_3 94 
#define REMOTE_STOP 71 


// LCD constants
#define LCD_RS A5
#define LCD_E A4
#define LCD_D4 6
#define LCD_D5 7
#define LCD_D6 8
#define LCD_D7 9

// Other constants 
#define LED_ARRAY_SIZE 3
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

byte LEDArray[LED_ARRAY_SIZE] = {LED1, LED2, LED3};
byte LEDStateArray[LED_ARRAY_SIZE] = {LOW, LOW, LOW};


void turnOffAllLEDs(){
  for(int i = 0; i < LED_ARRAY_SIZE; i++){
    LEDStateArray[i] = LOW;
    digitalWrite(LEDArray[i], LEDStateArray[i]);
  }
}

// initialise LED modes
void initLEDModes(){
  for(int i = 0; i < LED_ARRAY_SIZE; i++){
    pinMode(LEDArray[i], OUTPUT);
  }
}



void clearLCD(){
  lcd.clear();
}




void displayOnLCD( int command, String text){
  for(int i = text.length(); i<16; i++){
    text += " ";
  }
  lcd.setCursor(0,0);
  lcd.print(command);
  lcd.setCursor(0,1);
  lcd.print(text);
}



void toggleLEDs(int command){
  switch (command){
    case REMOTE_0:
      turnOffAllLEDs();
      displayOnLCD(command, "All LEDs OFF");
      break; 
    case REMOTE_1:
      toggleLEDFromIndex(0);
      if(LEDStateArray[0] == HIGH){
        displayOnLCD(command, "Green LED On");
      }else{
        displayOnLCD(command, "Green LED Off");
      }
      break;
    case REMOTE_2:
      toggleLEDFromIndex(1);
      if(LEDStateArray[1] == HIGH){
        displayOnLCD(command, "Yellow LED On");
      }else{
        displayOnLCD(command, "Yellow LED Off");
      }
      break;
    case REMOTE_3:
      toggleLEDFromIndex(2);
      if(LEDStateArray[2] == HIGH){
        displayOnLCD(command, "Red LED On");
      }else{
        displayOnLCD(command, "Red LED Off");
      }
      break;
    case REMOTE_STOP:
      clearLCD();
      break;
    default:
      displayOnLCD(command, "Try again!");
      break; 
  }
}



void toggleLEDFromIndex(int index){
  if(LEDStateArray[index] == HIGH){
    LEDStateArray[index] = LOW;
  }else{
    LEDStateArray[index] = HIGH;
  }
  digitalWrite(LEDArray[index], LEDStateArray[index]);
}

void setup() {
  IrReceiver.begin(IR_RECEIVER);
  lcd.begin(16, 2);
  initLEDModes();
}


void loop() {
  // activity: 
  // 0, 1, 2, 3, FUNC/STOP
  // 0 -> power off all LEDs
  // 1 -> toggle LED1 pin 12
  // 2 -> toggle LED2 pin 11
  // 3 -> toggle LED2 pin 10

  // LCD:  1st line -> data (command);
  //       2nd line -> "message"

  // FUNC/STOP -> clear LCD

  // LEDs -> use arrays & functions 

  if(IrReceiver.decode()){
    IrReceiver.resume();
    int command = IrReceiver.decodedIRData.command;
    toggleLEDs(command);
  }
}
