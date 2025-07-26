#define PR A0
 

void setup() {
  Serial.begin(115200);

}

void loop() {
  Serial.println(analogRead(PR));
  delay(100);
}
