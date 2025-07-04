
#define LED_PIN 7

int a; //uninitialised variable of int data type. [range = -32768 to 32767]

int b = 10; //int variable containing 10 as value.

long c = 2000000; //similar to integer but with wider range. [range = -2147483648 to 2147483647]

float c = 1.25; //can store decimal values.

double d = 3.14;  //same as float but more precised 

bool e = HIGH; //can store boolean values [0 or 1 | true or false | HIGH or LOW] 

String f = "Hello world i am using Arduino!!";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(b);
  b = c + d; 
  Serial.println(b);
}

void loop() {
  // put your main code here, to run repeatedly:

}
