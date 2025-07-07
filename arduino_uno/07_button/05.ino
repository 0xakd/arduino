#define BUTTON_PIN 2
#define LED_PIN 12

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

}

void loop() {
  if (digitalRead (BUTTON_PIN) == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    delay(5000);
  }
  else {
    digitalWrite(LED_PIN, LOW);
  }
     
}
