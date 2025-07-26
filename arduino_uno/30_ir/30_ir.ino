// This Code is written for IRremote v2.6 library.

#include <IRremote.h>
#define IR_RECIEVER 5

IRrecv irrecv(IR_RECIEVER);
decode_results results;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();
}

void loop() {
  if(irrecv.decode(&results)){
    irrecv.resume();
    Serial.println(results.value, HEX);
  }
}
