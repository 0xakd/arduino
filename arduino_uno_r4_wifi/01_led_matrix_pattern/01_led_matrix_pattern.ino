#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

const uint32_t triangle[] = {
  0xfff801bf,
	0xda65a65b,
	0xfd801fff,
};


void setup() {
  // put your setup code here, to run once:
  matrix.begin();
  matrix.clear();
  matrix.loadFrame(triangle);
}

void loop() {
  // put your main code here, to run repeatedly:

}
