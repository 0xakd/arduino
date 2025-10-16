#include <LiquidCrystal.h>
#include <IRremote.h>
#include <EEPROM.h>


#define USS_ECHO 3
#define USS_TRIGGER 4

#define WARNING_LED 11
#define ERROR_LED 12
#define LIGHT_LED 10

#define PHOTORESISTOR A0

#define LCD_RS A5
#define LCD_E A4
#define LCD_D4 6
#define LCD_D5 7
#define LCD_D6 8
#define LCD_D7 9

// IR button mapping 
#define IR_BUTTON_PLAY 64
#define IR_BUTTON_OFF 69
#define IR_BUTTON_EQ 25
#define IR_BUTTON_UP 9
#define IR_BUTTON_DOWN 7

// lcd mode
#define LCD_MODE_DISTANCE 0
#define LCD_MODE_SETTINGS 1
#define LCD_MODE_LUMINOSITY 2


#define BUTTON 2

#define IR_RECEIVER 5


#define LOCK_DISTANCE 10.0
#define WARNING_DISTANCE 50.0

#define DISTANCE_UNIT_CM 0
#define DISTANCE_UNIT_IN 1  

#define CM_TO_IN 0.39301

#define EEPROM_ADDRESS_DISTANCE_UNIT 50

// --time functionalities--
unsigned long lastTimeUSSTrigger = millis();
unsigned long ussTriggerDelay = 60;

// Warning LED                                                                            
unsigned long lastTimeWarningLEDBlinked = millis();
unsigned long warningLEDBlinkDelay = 500;  
bool warningLEDState = LOW;

// Error LED
unsigned long lastTimeErrorLEDBlinked = millis();
unsigned long errorLEDBlinkDelay = 300;  
bool errorLEDState = LOW;

// BUTTON
unsigned long lastTimeButtonPresses = millis();
unsigned long debounceDelay = 300; 
bool buttonState;
bool newButtonState;

// PHOTORESISTOR
unsigned long lastTimeLuminosityRead = millis();
unsigned long readLuminosityDelay = 100; 


// LCD
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

volatile unsigned long pulseInTimeBegin;
volatile unsigned long pulseInTimeEnd;
volatile bool newDistanceAvailable = false;

double prevDistance = 400.00;

bool isLocked = false;

int distanceUnit = DISTANCE_UNIT_CM;

int lcdMode = LCD_MODE_DISTANCE;



void triggerUSS() {
  digitalWrite(USS_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(USS_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(USS_TRIGGER, LOW);
}

double usDistance() {
  double duration = pulseInTimeEnd - pulseInTimeBegin;
  double distance = duration / 58.00;
  if (distance > 400.00) {
    return prevDistance;
  }
  distance = prevDistance * 0.6 + distance * 0.4;
  prevDistance = distance;
  return distance;
}


void echoInterrupt() {
  if (digitalRead(USS_ECHO) == HIGH) {
    pulseInTimeBegin = micros();
  } else {
    pulseInTimeEnd = micros();
    newDistanceAvailable = true;
  }
}






void toggleWarningLED(){
  warningLEDState = ((warningLEDState == HIGH) ? LOW : HIGH);
  digitalWrite(WARNING_LED, warningLEDState);
}

void toggleErrorLED(){
  errorLEDState = ((errorLEDState == HIGH) ? LOW : HIGH);
  digitalWrite(ERROR_LED, errorLEDState);
}



void setWarningLEDBLinkRateFromDistance(double distance){
  // 0 .. 400 -> 0 .. 1600ms
  warningLEDBlinkDelay = distance * 4;
}





void lock(){
  if(!isLocked){
    isLocked = true;
    warningLEDState = LOW;
    errorLEDState = LOW;
  } 
}



void unlock(){
  if(isLocked){
    isLocked = false;
    errorLEDState = LOW;
    digitalWrite(ERROR_LED, errorLEDState);
    lcd.clear();
  }
}




void displayOnLCD(double distance){
  if(isLocked){
    lcd.setCursor(0, 0);
    lcd.print("!!! Obstacle !!!       ");
    lcd.setCursor(0, 1);
    lcd.print("Press to unlock,      ");  
  }else if(lcdMode == LCD_MODE_DISTANCE){
    lcd.setCursor(0, 0);
    lcd.print("Dist: ");

    if(distanceUnit == DISTANCE_UNIT_IN){
      lcd.print(distance * CM_TO_IN);
      lcd.print(" in       ");
    }else{
      lcd.print(distance);
      lcd.print(" cm       ");
    }


    lcd.setCursor(0, 1);
    if(distance  > WARNING_DISTANCE){
      lcd.print("No Obstacle.       ");
    }else{
      lcd.print("!! Warning !!      ");   
    }
     
  }
}


void handleIRCommand(long command){
  switch (command){
    case IR_BUTTON_PLAY:
      unlock();
      break;
    case IR_BUTTON_OFF:
      resetSettingsToDefault();
      break;
    case IR_BUTTON_EQ:
      toggleDistanceUnit();
      break;
    case IR_BUTTON_UP:
      toggleLCDScreen(true);
      break;
    case IR_BUTTON_DOWN:
      toggleLCDScreen(false);   
      break;
    default:
      break;

  } 
}

void toggleDistanceUnit(){
  if(distanceUnit == DISTANCE_UNIT_CM){
    distanceUnit = DISTANCE_UNIT_IN;
  }else{
    distanceUnit = DISTANCE_UNIT_CM;
  }
  EEPROM.write(EEPROM_ADDRESS_DISTANCE_UNIT, distanceUnit);
}







void toggleLCDScreen(bool next){
  switch (lcdMode){
    case LCD_MODE_DISTANCE:
      lcdMode = (next) ? LCD_MODE_SETTINGS : LCD_MODE_LUMINOSITY;
      break;
    case LCD_MODE_SETTINGS:
      lcdMode = (next) ? LCD_MODE_LUMINOSITY : LCD_MODE_DISTANCE;
      break;
    case LCD_MODE_LUMINOSITY:
      lcdMode = (next) ? LCD_MODE_DISTANCE : LCD_MODE_SETTINGS;
      break;
    default:
      lcdMode = LCD_MODE_DISTANCE;
      break;
  }

  lcd.clear();

  if(lcdMode == LCD_MODE_SETTINGS){
    lcd.setCursor(0, 0);
    lcd.print("Press OFF to       ");
    lcd.setCursor(0, 1);
    lcd.print("reset Settings.    ");
  }
}



void resetSettingsToDefault(){
  if(lcdMode == LCD_MODE_SETTINGS){
    if(distanceUnit = DISTANCE_UNIT_IN){
      toggleDistanceUnit();
    }    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LCD have");
    lcd.setCursor(0, 1);
    lcd.print("been reset.");
  }
}

void setLightLEDFromLuminosity(int luminosity){
  byte brightness = 255 - luminosity / 4;
  analogWrite(LIGHT_LED, brightness);
}

void printLuminosityonLCD(int luminosity){
  if(!isLocked && lcdMode == LCD_MODE_LUMINOSITY){
    lcd.setCursor(0, 0);
    lcd.print("Luminosity: ");
    lcd.print(luminosity);
    lcd.print("       ");
  }
}




void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2); 
  IrReceiver.begin(IR_RECEIVER);
  pinMode(USS_ECHO, INPUT);
  pinMode(USS_TRIGGER, OUTPUT);
  pinMode(WARNING_LED, OUTPUT);
  pinMode(ERROR_LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(LIGHT_LED, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(USS_ECHO), echoInterrupt, CHANGE);
  distanceUnit = EEPROM.read(EEPROM_ADDRESS_DISTANCE_UNIT);
  if(distanceUnit == 255){
    distanceUnit = DISTANCE_UNIT_CM;
  }

  buttonState = digitalRead(BUTTON);
  lcd.print("Initialising...");
  delay(1000);
  lcd.clear();
}


void loop() {
  unsigned long timeNow = millis();
  if (timeNow - lastTimeUSSTrigger > ussTriggerDelay) {
    lastTimeUSSTrigger += ussTriggerDelay;
    triggerUSS();
  }

  if(isLocked){
    if(timeNow - lastTimeErrorLEDBlinked > errorLEDBlinkDelay){
      lastTimeErrorLEDBlinked += errorLEDBlinkDelay;
      toggleErrorLED();
      toggleWarningLED();
    }

    if(timeNow - lastTimeButtonPresses > debounceDelay){
      byte newButtonState = digitalRead(BUTTON);
      if(newButtonState != buttonState){
        lastTimeButtonPresses = timeNow;
        buttonState = newButtonState;
        if(buttonState == LOW){
          unlock();
        }
      }
    }
  }else{
    if (timeNow - lastTimeWarningLEDBlinked > warningLEDBlinkDelay){
      lastTimeWarningLEDBlinked += warningLEDBlinkDelay;
      toggleWarningLED();
    }

  }

  if(IrReceiver.decode()){
    IrReceiver.resume();
    long command = IrReceiver.decodedIRData.command;
    handleIRCommand(command);
  }


  if (newDistanceAvailable) {
    newDistanceAvailable = false;
    double distance = usDistance();
    setWarningLEDBLinkRateFromDistance(distance);
    displayOnLCD(distance);
    if(distance <= LOCK_DISTANCE){
      lock();
    }
  }

  if(timeNow - lastTimeLuminosityRead > readLuminosityDelay){
    lastTimeLuminosityRead += readLuminosityDelay;
    int luminosity = analogRead(PHOTORESISTOR);
    setLightLEDFromLuminosity(luminosity);
    printLuminosityonLCD(luminosity);    
  }

}
