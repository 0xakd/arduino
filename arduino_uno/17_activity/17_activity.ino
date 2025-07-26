#define LED1 8
#define LED2 9
#define LED3 10
#define BTN 2

unsigned long lastTimeButtonChanged = millis();
unsigned long debounceDelay = 40;
unsigned long lastTimeLedBlinked = millis();
unsigned long blinkDelay = 1000;

bool buttonState = LOW;
bool ledState = LOW;

int btnToggle = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BTN, INPUT);

}

void loop() {
  unsigned long timeNow = millis();

  // Task 1: pressed(LOW -> HIGH): toggle LED 2 & 3
  // toggle LEDs: power on 2, power off 3
  if(timeNow - lastTimeButtonChanged > debounceDelay){
    bool newButtonState = digitalRead(BTN);
    if(newButtonState != buttonState){
      lastTimeButtonChanged = timeNow;
      buttonState  = newButtonState;
      if(buttonState == HIGH){
        if(btnToggle == 1){
          btnToggle = 2;
          digitalWrite(LED2, HIGH);
          digitalWrite(LED3, LOW);
        }else{
          btnToggle = 1;
          digitalWrite(LED2, LOW);
          digitalWrite(LED3, HIGH);
        }
        
      }
    }
  }

  // blink led 1 every 1000ms
  if(timeNow - lastTimeLedBlinked > blinkDelay){
    lastTimeLedBlinked += blinkDelay;
    if(ledState == HIGH){
      ledState = LOW;
    }else{
      ledState = HIGH;
    }
    digitalWrite(LED1, ledState);
  }

}
