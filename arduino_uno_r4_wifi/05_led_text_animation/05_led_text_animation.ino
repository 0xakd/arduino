#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;


void setup() {
  // put your setup code here, to run once:
  matrix.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  const char text[] = "  hello world";  
  matrix.textScrollSpeed(50);
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(text);
  matrix.endText(SCROLL_LEFT); 
  delay(200);
  matrix.loadSequence(LEDMATRIX_ANIMATION_SPINNING_COIN);
  matrix.play(true);
  delay(1000);
}
