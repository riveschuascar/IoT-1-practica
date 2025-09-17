#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int tPin, int ePin) {
  trigPin = tPin;
  echoPin = ePin;
  timeout_us = 30000UL;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
}

int UltrasonicSensor::readDistanceCm() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long dur = pulseIn(echoPin, HIGH, timeout_us);
  if (dur == 0UL) {
    // timeout -> considerar inválido
    return -1;
  }
  float cm = (dur * 0.0343f) / 2.0f;  // velocidad sonido ~343 m/s
  return (int)(cm + 0.5f);
}
