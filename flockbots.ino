#include <Servo.h>

#define HIGH_BUMP_PIN 2
#define BREAK_BEAM_PIN 3

#define BAT_PIN A11
#define ANALOG_PIN_RATIO 0.00488
#define BAT_RATIO 2.26

#define GRIPPER_PIN 4
#define GRIPPER_OPEN 55
#define GRIPPER_CAN 60
#define GRIPPER_CLOSE 70

#define CAMERA_PIN 44
#define CAMERA_CENTER 90

#define L_SERVO_PIN 45
#define L_WHEEL_CLOCK 18
#define L_WHEEL_DIRECTION 31
#define L_WHEEL_CENTER 89

#define R_SERVO_PIN 46
#define R_WHEEL_CLOCK 19
#define R_WHEEL_DIRECTION 32
#define R_WHEEL_CENTER 92

#define LD_IR_PIN A6
#define L_IR_PIN A7
#define C_IR_PIN A8
#define R_IR_PIN A9
#define RD_IR_PIN A10

int leftTicks = 0;
int rightTicks = 0;

Servo gripper;
Servo camera;
Servo lWheel;
Servo rWheel;

void flockBotSetup() {
  attachInterrupt(digitalPinToInterrupt(L_WHEEL_CLOCK), updateLeftTicks, CHANGE);
  attachInterrupt(digitalPinToInterrupt(R_WHEEL_CLOCK), updateRightTicks, CHANGE);
  gripper.attach(GRIPPER_PIN);
  gripperOpen();
  camera.attach(CAMERA_PIN);
  setCamera(CAMERA_CENTER);
  lWheel.attach(L_SERVO_PIN);
  lWheel.write(L_WHEEL_CENTER);
  rWheel.attach(R_SERVO_PIN);
  rWheel.write(R_WHEEL_CENTER);
  pinMode(HIGH_BUMP_PIN, INPUT_PULLUP);
  pinMode(BREAK_BEAM_PIN, INPUT_PULLUP);
}

int readBump() {
  return digitalRead(HIGH_BUMP_PIN);
}

int readIR(int sensorNum) {
  return analogRead(sensorNum);
}

int readBreakBeam() {
  return digitalRead(BREAK_BEAM_PIN);
}

int getBatteryLevel() {
  return (analogRead(BAT_PIN) * ANALOG_PIN_RATIO * BAT_RATIO)*100;
}

void setGripper(int degree) {
  gripper.write(degree);
}

void gripperGrabCan() {
  setGripper(GRIPPER_CAN);
}

void gripperOpen() {
  setGripper(GRIPPER_OPEN);
}

void gripperClose() {
  setGripper(GRIPPER_CLOSE);
}

void setCamera(int degree) {
  if(degree < 30) {
    degree = 30;
  }
  camera.write(degree);
}

int getLeftTicks() {
  return leftTicks;
}

int getRightTicks() {
  return rightTicks;
}

void setLeftWheel(int degree) {
  lWheel.write(degree);
}

void setRightWheel(int degree) {
  rWheel.write(degree);
}

void updateLeftTicks() {
  leftTicks  += digitalRead(L_WHEEL_DIRECTION)?1:-1;
}

void updateRightTicks() {
  rightTicks  += digitalRead(R_WHEEL_DIRECTION)?-1:1;
}



