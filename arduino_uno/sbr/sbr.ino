#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "PID_v1.h"
#include "Wire.h"

// Motor driver pins
const int ENA = 3;
const int IN1 = 4;
const int IN2 = 5;
const int ENB = 6;
const int IN3 = 7;
const int IN4 = 8;

// MPU variables
MPU6050 mpu;
bool dmpReady = false;
uint8_t mpuIntStatus;
uint8_t devStatus;
uint16_t packetSize;
uint16_t fifoCount;
uint8_t fifoBuffer[64];
Quaternion q;
VectorFloat gravity;
float ypr[3];
volatile bool mpuInterrupt = false;

// PID control
double input, output;
double setpoint = 180;  // balanced pitch
double Kp = 67, Ki = 80, Kd = 2.0;
PID pid(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);
double fallLimit = 45;  // acceptable range to stay balanced

void dmpDataReady() {
  mpuInterrupt = true;
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Setup motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  stopMotors();

  // Initialize MPU6050
  mpu.initialize();
  devStatus = mpu.dmpInitialize();

  // Set offsets (you can calibrate and adjust)
  mpu.setXGyroOffset(53);
  mpu.setYGyroOffset(-6);
  mpu.setZGyroOffset(-40);
  mpu.setZAccelOffset(1790);

  if (devStatus == 0) {
    mpu.setDMPEnabled(true);
    attachInterrupt(digitalPinToInterrupt(2), dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();

    pid.SetMode(AUTOMATIC);
    pid.SetSampleTime(10);
    pid.SetOutputLimits(-255, 255);

    Serial.println("DMP ready. PID and Motors engaged.");
  } else {
    Serial.print("DMP init failed (code ");
    Serial.print(devStatus);
    Serial.println(")");
  }
}

void loop() {
  if (!dmpReady || !mpuInterrupt) return;

  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();
  fifoCount = mpu.getFIFOCount();

  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    mpu.resetFIFO();
    Serial.println("FIFO overflow!");
    return;
  }

  if (mpuIntStatus & 0x02) {
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
    mpu.getFIFOBytes(fifoBuffer, packetSize);
    fifoCount -= packetSize;

    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    input = ypr[1] * 180 / M_PI + 180;
    pid.Compute();

    Serial.print("Pitch: ");
    Serial.print(input);
    Serial.print(" | PID Output: ");
    Serial.println(output);

    if (abs(input - setpoint) < fallLimit) {
      int pwm = constrain(abs(output), 100, 255);

      if (output < 0) moveBackward(pwm);
      else if (output > 0) moveForward(pwm);
      else stopMotors();
    } else {
      stopMotors();  // robot fell over or tilted too far
    }
  }
}

// Motor control functions
void moveForward(int power) {
  analogWrite(ENA, power);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, power);
  digitalWrite(IN3, LOW);   
  digitalWrite(IN4, HIGH);  
}

void moveBackward(int power) {
  analogWrite(ENA, power);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  analogWrite(ENB, power);
  digitalWrite(IN3, HIGH);  
  digitalWrite(IN4, LOW); 
}

void stopMotors() {
  analogWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, 0);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
