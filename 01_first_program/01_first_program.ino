void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);
}

void loop() {
  //turn on the led
  digitalWrite(8, HIGH);
  
  delay(500); // 500ms delay after turning on the led.

  //turns off the led
  digitalWrite(8, LOW);
  delay(500);
}

