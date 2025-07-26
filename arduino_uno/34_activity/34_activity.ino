#define PTR A0
#define LED1 10
#define LED2 12

void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  int value = analogRead(PTR);
  Serial.println(value);
  analogWrite(LED1, value/4);

  if(value < 50){
    digitalWrite(LED2, HIGH);
  }else{
    digitalWrite(LED2, LOW);
  }
}
