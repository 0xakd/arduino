#define LED 12

unsigned long previousTimeLEDBlink = millis();
unsigned long timeIntervalLEDBlink = 500;

int LED_State = LOW;

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
      timeIntervalLEDBlink = data; 
    }
  }

  unsigned long timeNow = millis();
  if(timeNow - previousTimeLEDBlink > timeIntervalLEDBlink){
    if(LED_State == LOW){
      LED_State = HIGH;
    }
    else{
      LED_State = LOW;
    }
    
    digitalWrite(LED, LED_State);
    previousTimeLEDBlink += timeIntervalLEDBlink;
  }

}
