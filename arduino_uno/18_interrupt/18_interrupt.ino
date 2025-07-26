#define LED 8
#define BTN 2

bool LEDState = LOW;
volatile bool buttonReleased = false;

void toggleLED(){
  if(LEDState == HIGH){
    LEDState = LOW;
  }else{
    LEDState = HIGH;
  }
  digitalWrite(LED, LEDState);
}

void buttonReleasedInterrupt(){
  buttonReleased = true;
}


void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BTN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(BTN), buttonReleasedInterrupt, FALLING);

}

void loop() {
  if(buttonReleased){
    buttonReleased = false;
    toggleLED();
  }

}
