#define BTN 2
#define LED 8

volatile unsigned long lastTimeButtonReleased = millis();
unsigned long debounceDelay = 40;

bool LEDState = LOW;
volatile bool buttonReleased = false;


void toggleLED(){
  if(LEDState == LOW){
    LEDState = HIGH;
  }else{
    LEDState = LOW;
  }
  digitalWrite(LED, LEDState);
}

void buttonReleasedInterrupt(){
  unsigned long timeNow = millis();
  if(timeNow - lastTimeButtonReleased > debounceDelay){
    lastTimeButtonReleased = timeNow;
    buttonReleased = true;
  }
}


void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BTN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BTN), buttonReleasedInterrupt, FALLING);
}

void loop() {
  if(buttonReleased){
    buttonReleased = false;
    toggleLED();
  }
}
