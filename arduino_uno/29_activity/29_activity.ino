#include <LiquidCrystal.h>
#define LCD_RS A5
#define LCD_E A4
#define LCD_D4 6
#define LCD_D5 7
#define LCD_D6 8
#define LCD_D7 9
#define USS_TRIGGER 4
#define USS_ECHO 3

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

volatile unsigned long lastTimeUSSTrigger = millis();
volatile unsigned long USSTriggerDelay = 60;

volatile unsigned long pulseTimeBegin;
volatile unsigned long pulseTimeEnd;
volatile bool newDistanceAvailable = false;

double previousDistance = 400.00;

double distance;

void triggerUSS(){
  digitalWrite(USS_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(USS_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(USS_TRIGGER, LOW);
} 

void getUSS_Distance(){
  double duration = pulseTimeEnd - pulseTimeBegin ;
  distance = duration / 58.00; 
  if(distance > 400.00){
    distance = previousDistance;
  }
  previousDistance = distance;
}


void echoPinInterrupt(){
  if(digitalRead(USS_ECHO) == HIGH){
    pulseTimeBegin = micros();
  }else{
    pulseTimeEnd = micros();
    newDistanceAvailable = true;
  }
}

void displayDataOnLCD(){
  lcd.setCursor(0, 0);
  lcd.print("Rate: ");
  lcd.print(USSTriggerDelay);
  lcd.print(" ms. ");

  lcd.setCursor(0, 1);
  lcd.print("Dist.: ");
  lcd.print(distance);
  lcd.print(" cm. ");
}

void setup() {
  Serial.begin(115200); 
  lcd.begin(16, 2);
  pinMode(USS_ECHO, INPUT);
  pinMode(USS_TRIGGER, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(USS_ECHO), echoPinInterrupt, CHANGE);

}

void loop() {
  unsigned long timeNow = millis();
  if(timeNow - lastTimeUSSTrigger > USSTriggerDelay ){
    lastTimeUSSTrigger += USSTriggerDelay;
    triggerUSS();
  }

  if(newDistanceAvailable){
    newDistanceAvailable = false;
    getUSS_Distance();
    displayDataOnLCD();
  }
}
