#include <IRremote.h>

#define IR_RECIEVER 5
#define REMOTE_POWER 69
#define REMOTE_P_P 64
#define REMOTE_PREV 68
#define REMOTE_NEXT 67
#define REMOTE_1 12
#define REMOTE_2 24
#define REMOTE_3 94

void setup() {
  Serial.begin(115200);
  IrReceiver.begin(IR_RECIEVER);
}

void loop() {
  if(IrReceiver.decode()){
    IrReceiver.resume();
    // Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    int command = IrReceiver.decodedIRData.command;
    Serial.println(command);
    switch (command){
      case REMOTE_POWER:
        Serial.println("Power button was pressed!");
        break;          
      case REMOTE_P_P:
        Serial.println("Play/Pause button was pressed!");
        break;        
      case REMOTE_PREV:
        Serial.println("Previous button was pressed!");
        break;        
      case REMOTE_NEXT:
        Serial.println("Next button was pressed!");
        break;        
      case REMOTE_1:
        Serial.println("1 button was pressed!");
        break;        
      case REMOTE_2:
        Serial.println("2 button was pressed!");
        break;        
      case REMOTE_3:
        Serial.println("3 button was pressed!");
        break;        
      default :
        Serial.println("Try Pressing another button!");
        break;          
    }

  }
}
