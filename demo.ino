#define LD_IR_PIN A6
#define L_IR_PIN A7
#define C_IR_PIN A8
#define R_IR_PIN A9
#define RD_IR_PIN A10

#define L_WHEEL_CENTER 90
#define R_WHEEL_CENTER 92

void setup() {
  Serial.begin(9600);
  flockBotSetup();
  Serial.println("send a character to move to next test");
}

int state = 0;
int output = -1;

void loop() {
  switch(state) {
    case 0:
      Serial.print("bumper value: ");
      output = readBump();
      break;
    case 1:
      Serial.print("break value: ");
      output = readBreakBeam();
      break;
    case 2:
      Serial.print("Left IR value: ");
      output = readIR(L_IR_PIN);
      break;
    case 3:
      Serial.print("Left Diagonal IR value: ");
      output = readIR(LD_IR_PIN);
      break;
    case 4:
      Serial.print("Center IR value: ");
      output = readIR(C_IR_PIN);
      break;
    case 5:
      Serial.print("Right Diagonal IR value: ");
      output = readIR(RD_IR_PIN);
      break;
    case 6:
      Serial.print("Right IR value: ");
      output = readIR(R_IR_PIN);
      break;
    case 7:
      Serial.print("Battery value: ");
      output = getBatteryLevel();
      break;
    case 8:
      Serial.print("Gripping ");
      output = -1;
      gripperOpen();
      delay(200);
      gripperGrabCan();
      delay(200);
      gripperClose();
      delay(200);
      gripperOpen();
      break;
    case 9:
      Serial.print("Camera Waggling ");
      output = -1;
      setCamera(100);
      delay(200);
      setCamera(80);
      delay(200);
      break;
    case 10:
      Serial.print("Right wheel forward, ticks:");
      setRightWheel(80);
      output = getRightTicks();
      break;
    case 11:
      Serial.print("Right wheel backward, ticks:");
      setRightWheel(100);
      output = getRightTicks();
      break;
    case 12:
      setRightWheel(R_WHEEL_CENTER);
      Serial.print("Left wheel backward, ticks:");
      setLeftWheel(80);
      output = getLeftTicks();
      break;
    case 13:
      Serial.print("Left wheel forward, ticks: ");
      setLeftWheel(100);
      output = getLeftTicks();
      break;
    case 14:
      setLeftWheel(L_WHEEL_CENTER);
      Serial.print("Restarting");
      output = -1;
      state = 0;
      break;
  }
  if(output != -1) {
    Serial.println(output);
  }
  else {
    Serial.println();
  }
  if(Serial.available() > 0) {
    Serial.read();
    state++;
  }
  delay(250);
}

