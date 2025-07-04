#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

void setup() {
  // put your setup code here, to run once:
  matrix.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  matrix.loadFrame(LEDMATRIX_BLUETOOTH);
  delay(1000);
  matrix.clear();
  delay(100);
  matrix.loadFrame(LEDMATRIX_BOOTLOADER_ON);
  delay(1000);
  matrix.clear();
  delay(100);
  matrix.loadFrame(LEDMATRIX_CHIP);
  delay(1000);
  matrix.clear();
  delay(100);
  matrix.loadFrame(LEDMATRIX_CLOUD_WIFI);
  delay(1000);
  matrix.clear();
  delay(100);
  matrix.loadFrame(LEDMATRIX_DANGER);
  delay(1000);
  matrix.clear();
  delay(100);
  matrix.loadFrame(LEDMATRIX_EMOJI_BASIC);
  delay(1000);
  matrix.clear();
  delay(100);
  matrix.loadFrame(LEDMATRIX_EMOJI_HAPPY);
  delay(1000);
  matrix.clear();
  delay(100);
  matrix.loadFrame(LEDMATRIX_EMOJI_SAD);
  delay(1000);
  matrix.clear();
  delay(100);
  matrix.loadFrame(LEDMATRIX_HEART_BIG);
  delay(1000);
  matrix.clear();
  delay(100);
  matrix.loadFrame(LEDMATRIX_HEART_SMALL);
  delay(1000);
  matrix.clear();
  delay(100);
  matrix.loadFrame(LEDMATRIX_LIKE);
  delay(1000);
  matrix.clear();
  delay(100);
  matrix.loadFrame(LEDMATRIX_MUSIC_NOTE);
  delay(1000);
  matrix.clear();
  delay(100);
  matrix.loadFrame(LEDMATRIX_RESISTOR);
  delay(1000);
  matrix.clear();
  delay(100);
  matrix.loadFrame(LEDMATRIX_UNO);
  delay(1000);
  matrix.clear();
  delay(100);
  
}
