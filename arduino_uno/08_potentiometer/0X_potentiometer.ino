#define PPM A1
#define LED 12 

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(LED, analogRead(PPM)/4);
}
