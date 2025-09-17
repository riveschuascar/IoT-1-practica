#include "ServoMotor.h"

SmartDoor::SmartDoor(byte servoPin) {
  pin = servoPin;
  lastAngle = -1;
  attached = false;
}

void SmartDoor::begin() {
  servo.attach(pin, 500, 2500);
  attached = true;
  writeAngle(0);
}

void SmartDoor::writeAngle(int angle) {
  if (!attached) return;
  if (angle == lastAngle) return;

  servo.write(angle);
  lastAngle = angle;

  Serial.print("Servo -> ");
  Serial.print(angle);
  Serial.println(" deg");
}

int SmartDoor::getLastAngle() {
  return lastAngle;
}
