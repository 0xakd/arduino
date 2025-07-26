#define greenLED 10
#define yellowLED 11
#define redLED 12

#define ECHO_PIN 3
#define TRIGGER_PIN 4

unsigned long lastTimeUltrasonicTrigger = millis();
unsigned long ultrasonicDelay = 60;


volatile unsigned long PulseInTimeBegin;
volatile unsigned long PulseInTimeEnd;
volatile bool newDistanceAvailable = false;


void triggerUltrasonicSensor(){
  digitalWrite(TRIGGER_PIN,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIGGER_PIN, LOW);
}


double getUltrasonicDistance(){
  double duration = PulseInTimeEnd - PulseInTimeBegin;
  double distance = duration / 58.00;
  return distance;
} 




void echoPinInterrupt(){
  if(digitalRead(ECHO_PIN) == HIGH){
    PulseInTimeBegin = micros();
  }else{
    PulseInTimeEnd = micros();
    newDistanceAvailable = true;
  }
}


void powerOnLEDs(double distance){
  if (distance >= 100){
      digitalWrite(greenLED, HIGH);
      digitalWrite(redLED, LOW);
      digitalWrite(yellowLED, LOW);
    }else if(distance >= 15 && distance < 100){
      digitalWrite(greenLED, LOW);
      digitalWrite(redLED, LOW);
      digitalWrite(yellowLED, HIGH);
    }else{
      digitalWrite(greenLED, LOW);
      digitalWrite(redLED, HIGH);
      digitalWrite(yellowLED, LOW);
    }
}


void setup() {
  Serial.begin(115200);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), echoPinInterrupt, CHANGE);
}

void loop() {
  unsigned long timeNow = millis();
  if(timeNow - lastTimeUltrasonicTrigger > ultrasonicDelay){
    lastTimeUltrasonicTrigger += ultrasonicDelay;
    triggerUltrasonicSensor();
  }
  
  if(newDistanceAvailable){
    newDistanceAvailable = false;
    double distance = getUltrasonicDistance();
    powerOnLEDs(distance);
    Serial.println(distance);
  }
  // distance > 100cm -> green LED (10)
  // distance > 10-100cm -> yellow LED (11)
  // distance < 15cm -> red LED (12)
}
