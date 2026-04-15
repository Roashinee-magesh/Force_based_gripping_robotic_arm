#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver();

// Servo limits
#define SERVOMIN  120
#define SERVOMAX  500

// Channels
#define SERVO_BASE 0
#define SERVO_ARM 1
#define SERVO_GRIPPER 2

// FSR Pins
#define FSR1 34
#define FSR2 35

// Positions
int basePos = 300;
int armPos = 300;
int gripperPos = 300;

void setup() {
  Serial.begin(115200);

  pca9685.begin();
  pca9685.setPWMFreq(50);

  pinMode(FSR1, INPUT);
  pinMode(FSR2, INPUT);

  Serial.println("Controls:");
  Serial.println("a/d -> Base Left/Right");
  Serial.println("w/s -> Arm Up/Down");
  Serial.println("g -> Close Gripper (FSR stop)");
  Serial.println("o -> Open Gripper");
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();

    switch (cmd) {

      case 'a': moveBase(-10); break;
      case 'd': moveBase(10); break;

      case 'w': moveArm(-10); break;
      case 's': moveArm(10); break;

      case 'g': closeGripper(); break;
      case 'o': openGripper(); break;
    }
  }
}

// ================= BASE =================
void moveBase(int step) {
  basePos += step;

  basePos = constrain(basePos, SERVOMIN, SERVOMAX);

  pca9685.setPWM(SERVO_BASE, 0, basePos);

  Serial.print("Base Position: ");
  Serial.println(basePos);
}

// ================= ARM =================
void moveArm(int step) {
  armPos += step;

  armPos = constrain(armPos, SERVOMIN, SERVOMAX);

  pca9685.setPWM(SERVO_ARM, 0, armPos);

  Serial.print("Arm Position: ");
  Serial.println(armPos);
}

// ================= GRIPPER =================
void closeGripper() {
  Serial.println("Closing gripper...");

  while (true) {
    int fsr1_val = analogRead(FSR1);
    int fsr2_val = analogRead(FSR2);

    Serial.print("FSR1: "); Serial.print(fsr1_val);
    Serial.print(" | FSR2: "); Serial.println(fsr2_val);

    if (fsr1_val >= 11 || fsr2_val >= 11) {
      Serial.println("Object detected - Stop gripping");
      break;
    }

    gripperPos += 5;
    if (gripperPos > SERVOMAX) break;

    pca9685.setPWM(SERVO_GRIPPER, 0, gripperPos);
    delay(80);
  }
}

void openGripper() {
  Serial.println("Opening gripper...");

  while (gripperPos > SERVOMIN) {
    gripperPos -= 5;
    pca9685.setPWM(SERVO_GRIPPER, 0, gripperPos);
    delay(50);
  }
}
