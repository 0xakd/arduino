#define LED1 2
#define LED2 3
#define LED3 4
#define BTN 7

int BlinkState = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BTN, INPUT);
}


void loop() {
  if(digitalRead(BTN) == LOW){
    if(BlinkState == 1){
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
      BlinkState = 2;
    }else{
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      BlinkState = 1;
    }

    delay(300);
  }

  
}
