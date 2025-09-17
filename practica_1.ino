#include "UltrasonicSensor.h"
#include "MedianFilter.h"
#include "ServoMotor.h"

// --- CONFIG ---
const byte TRIG_PIN = 25;
const byte ECHO_PIN = 26;
const byte SERVO_PIN = 27;
const unsigned long LOOP_DELAY_MS = 100;

const float CLOSE_CM = 20.0f;
const float MEDIUM_CM   = 50.0f;


// objetos
UltrasonicSensor sensor(TRIG_PIN, ECHO_PIN);
SmartDoor door(SERVO_PIN);
MedianFilter3 medFilter;
bool useMedian = false;

void setup() {
  Serial.begin(115200);
  door.begin();
  // inicializamos buffer de la mediana con lecturas inválidas
  medFilter.reset();
  delay(3000);
}

void loop() {
    float raw = sensor.readDistanceCm();
    if (raw == -1) {
        return;
    }

    float valueToUse = raw;

    if (useMedian) {
        medFilter.push(raw);
        int med = medFilter.median();
        if (med != -1) valueToUse = med; // usar mediana válida
        Serial.print("Mediana: ");
        Serial.print(med);
        Serial.println(" cm");
    }

    // Determinar el ángulo objetivo
    int targetAngle;
    if (valueToUse > MEDIUM_CM) {
        targetAngle = 90;
    } else if (valueToUse > CLOSE_CM) {
        targetAngle = 45;
    } else {
        targetAngle = 0;
    }

    if (door.getLastAngle() != targetAngle) {
        door.writeAngle(targetAngle);
    }
    Serial.println(targetAngle);
    Serial.println(door.getLastAngle());
    delay(LOOP_DELAY_MS);
}
