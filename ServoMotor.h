#pragma once
#include <ESP32Servo.h>

class SmartDoor {
  private:
    Servo servo;
    byte pin;
    int lastAngle;
    bool attached;

  public:
    SmartDoor(byte servoPin);

    void begin();
    void writeAngle(int angle);
    int getLastAngle();
};
