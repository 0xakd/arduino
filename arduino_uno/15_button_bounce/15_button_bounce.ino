#define BTN 2

bool buttonState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(BTN, INPUT);
}

void loop() {

  bool newButtonState = digitalRead(BTN);

  if(newButtonState != buttonState){
    buttonState = newButtonState;
    if(buttonState == HIGH){
      Serial.println("Button pressed");
    }else{
      Serial.println("Button Released");
    }
  }

}
