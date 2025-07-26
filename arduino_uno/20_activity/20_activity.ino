#define BTN 2

volatile unsigned long lastTimeButtonPresses = millis();
unsigned long debounceDelay = 50;

volatile bool buttonPressed = false;

int count = 0;

void buttonPressedInterrupt(){
  unsigned long timeNow = millis();
  if(timeNow - lastTimeButtonPresses > debounceDelay){
    buttonPressed = true;
  }
}
 
void setup() {
  Serial.begin(115200);
  pinMode(BTN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BTN), buttonPressedInterrupt, RISING);
}

void loop() {
  if(buttonPressed){
    buttonPressed = false;
    count ++;
    Serial.print("Number of times button pressed: ");
    Serial.println(count);
  }
}
