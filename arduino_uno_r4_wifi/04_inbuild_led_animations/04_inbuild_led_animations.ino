#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

void setup() {
  // put your setup code here, to run once:
  matrix.begin();
}

void loop() {
  //some of the inbuilt animations of arduino uno r4 wifi.
  matrix.loadSequence(LEDMATRIX_ANIMATION_BOUNCING_BALL);
  matrix.play(true);
  delay(1000);

  matrix.loadSequence(LEDMATRIX_ANIMATION_HEARTBEAT);
  matrix.play(true);
  delay(1000);

  matrix.loadSequence(LEDMATRIX_ANIMATION_TETRIS_INTRO);
  matrix.play(true);
  delay(1000);
}
