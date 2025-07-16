#define LED1 12
#define LED2 11
#define LED3 10
#define PTM A2
#define BTN 2

unsigned long prevTimeBlinkState = millis();
unsigned long BlinkDelay = 500;

bool LED1State = LOW;
bool LED2State = LOW;
bool LED3State = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BTN, INPUT);
}

void loop() {
  //task 1 [set the blink Delay according to the serial communication]
  if (Serial.available() > 0) {
    int data = Serial.parseInt();
    if ((data >= 100) && (data <= 4000)) {
      BlinkDelay = data;
    }
  }

  unsigned long timeNow = millis();
  if (timeNow - prevTimeBlinkState > BlinkDelay) {
    if (LED1State == LOW) {
      LED1State = HIGH;
    } else {
      LED1State = LOW;
    }

    digitalWrite(LED1, LED1State);
    prevTimeBlinkState += BlinkDelay;
  }


  //task 2 [Set LED 2 brightness from potentiometer]
  analogWrite(LED2, analogRead(PTM) / 4);



  //task 3 [Power ON LED 3 when button is pressed]
  if (digitalRead(BTN) == HIGH) {
    digitalWrite(LED3, HIGH);
  } else {
    digitalWrite(LED3, LOW);
  }
}
