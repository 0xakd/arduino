#define BTN 2

unsigned long lastTimeButtonChanged = millis();
unsigned long debounceDelay = 40;

bool buttonState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(BTN, INPUT);
}

void loop() {
  unsigned long timeNow = millis();
  if(timeNow - lastTimeButtonChanged > debounceDelay){
    bool newButtonState = digitalRead(BTN);
    if(newButtonState != buttonState){
      lastTimeButtonChanged = timeNow;
      buttonState = newButtonState;
      if(buttonState == HIGH){
        Serial.println("button pressed");
      }else{
        Serial.println("button released");
      }
    }
  }
}
