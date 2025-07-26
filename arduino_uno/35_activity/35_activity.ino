#define PTR A0
#define ARRAY_SIZE 100

int luminositySamples[ARRAY_SIZE] = {0};
int counter = 0;
unsigned long lastTimeReadPTR = millis();
unsigned long PTRvalueDelay = 50;

int calculateAverage(){
  long array_sum = 0;
  for(int i = 0; i<ARRAY_SIZE; i++){
    array_sum += luminositySamples[i];
  }
  int avg = array_sum/ARRAY_SIZE;
  return avg;
}


void setup() {
  Serial.begin(115200);
}

void loop() {
  unsigned long timeNow = millis();
  if(timeNow - lastTimeReadPTR > PTRvalueDelay){
    lastTimeReadPTR += PTRvalueDelay;
    if(counter != 100){
      luminositySamples[counter] = analogRead(PTR);
      Serial.print(".");
      counter++;
    }else{
      Serial.println();
      Serial.print("Average of 100 photoresistor readings is: ");
      Serial.println(calculateAverage());
      counter = 0;
    }
  } 
}
