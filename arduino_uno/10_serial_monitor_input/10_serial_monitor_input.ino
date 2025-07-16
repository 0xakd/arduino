void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(10);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() > 0 ){
    // int var = Serial.parseInt();  // reads integer values.
    // long var = Serial.parseInt();   // reads larger integer values 
    // float var = Serial.parseFloat();    // reads float values
    // double var = Serial.parseFloat();   // reads larger float values 
    String var = Serial.readString();   // reads string values
    Serial.println(var);
  } 
}
