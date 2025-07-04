#include "Arduino_LED_Matrix.h"
#include "loading_animation.h"

ArduinoLEDMatrix matrix;


void setup() {
  // put your setup code here, to run once:
  matrix.loadSequence(animation);
  matrix.begin();

  matrix.play(true);  //use false to play once.
}

void loop() {
  // put your main code here, to run repeatedly:
  matrix.clear();
  delay(1000);
  matrix.play(true);
}
