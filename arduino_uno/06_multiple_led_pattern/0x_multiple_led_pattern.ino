#define LED_01 5
#define LED_02 6
#define LED_03 9
#define LED_04 10
#define LED_05 11





void setup() {
  // put your setup code here, to run once:
  pinMode(LED_01, OUTPUT);

  pinMode(LED_02, OUTPUT);

  pinMode(LED_03, OUTPUT);

  pinMode(LED_04, OUTPUT);

  pinMode(LED_05, OUTPUT);

}

void loop() {
  for(int i = 0; i <= 225; i++){
    analogWrite(LED_05, i);
    delay(1);
  }

  for(int i = 0; i <= 225; i++){
    analogWrite(LED_01, i);
    delay(1);
  }

  for(int i = 0; i <= 225; i++){
    analogWrite(LED_04, i);
    delay(1);
  }

  for(int i = 0; i <= 225; i++){
    analogWrite(LED_02, i);
    delay(1);
  }

  for(int i = 0; i <= 225; i++){
    analogWrite(LED_03, i);
    delay(1);
  }
  



  for(int i = 255; i >= 0; i--){
    analogWrite(LED_03, i);
    delay(1);
  }

  for(int i = 255; i >= 0; i--){
    analogWrite(LED_02, i);
    delay(1);
  }
  for(int i = 255; i >= 0; i--){
    analogWrite(LED_04, i);
    delay(1);
  }
  
  for(int i = 255; i >= 0; i--){
    analogWrite(LED_01, i);
    delay(1);
  }

  for(int i = 255; i >= 0; i--){
    analogWrite(LED_05, i);
    delay(1);
  }

}
