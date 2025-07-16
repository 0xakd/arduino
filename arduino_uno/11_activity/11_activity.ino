#define LED 12

int LED_State = LOW;
int BlinkDelay = 500;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(10); 
  pinMode(LED, OUTPUT);
}

void loop() {
  if(Serial.available() > 0){
    int data = Serial.parseInt();
    if(data >=100 && data <= 1000){
      BlinkDelay = data; 
    }
  }

  digitalWrite(LED, LED_State);
  delay(BlinkDelay);

  if(LED_State == LOW){
    LED_State = HIGH;
  }
  else{
    LED_State = LOW;
  }

}
