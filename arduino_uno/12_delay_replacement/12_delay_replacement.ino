#define LED1 12
#define LED2 11

unsigned long prevTimeLED1Blink = millis();
unsigned long timeIntervalLED1Blink = 470;

unsigned long prevTimeLED2Blink = millis();
unsigned long timeIntervalLED2Blink = 1300;

bool LED1State = LOW;
bool LED2State = LOW    ;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  unsigned long timeNow = millis();

  if(timeNow - prevTimeLED1Blink > timeIntervalLED1Blink){
    if(LED1State == LOW){
      LED1State = HIGH;
    }else{
      LED1State = LOW;
    }

    digitalWrite(LED1, LED1State);
    prevTimeLED1Blink += timeIntervalLED1Blink;
  } 

  if(timeNow - prevTimeLED2Blink > timeIntervalLED2Blink){
    if(LED2State == LOW){
      LED2State = HIGH;
    }else{
      LED2State = LOW;
    }

    digitalWrite(LED2, LED2State);
    prevTimeLED2Blink += timeIntervalLED2Blink;
  } 

}

