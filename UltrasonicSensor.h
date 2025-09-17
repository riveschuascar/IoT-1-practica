#pragma once
#include <Arduino.h>

class UltrasonicSensor {
  private:
    byte trigPin;
    byte echoPin;
    unsigned long timeout_us;

  public:
    UltrasonicSensor(int tPin, int ePin);
    
    // Devuelve distancia en cm (int). Si no hay lectura válida devuelve -1.
    int readDistanceCm();
};
