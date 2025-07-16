#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

char text[] = "  hello world";  

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  matrix.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    String newText = "  " + Serial.readString();
    if(newText.length() > 0){
      newText.toCharArray(text, sizeof(text));
    }
  }
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
