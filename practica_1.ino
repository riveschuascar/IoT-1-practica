#include "UltrasonicSensor.h"
#include "MedianFilter.h"
#include "ServoMotor.h"

// --- CONFIG ---
const byte TRIG_PIN = 25;
const byte ECHO_PIN = 26;
const byte SERVO_PIN = 27;
const unsigned long LOOP_DELAY_MS = 10;

const byte CRITICAL_CM = 20;
const byte MEDIUM_CM   = 50;


// objetos
UltrasonicSensor sensor(TRIG_PIN, ECHO_PIN);
SmartDoor door(SERVO_PIN);
MedianFilter3 medFilter;
bool useMedian = true;

void setup() {
  Serial.begin(115200);
  door.begin();
  // inicializamos buffer de la mediana con lecturas inválidas
  medFilter.reset();
  delay(100);
}

void loop() {
  int raw = sensor.readDistanceCm();  // -1 si inválido
  if (raw == -1) {
    Serial.println("Distancia: N/A");
    // criterios: no decidir con lectura inválida -> no mover servo
  } else {
    Serial.print("Distancia: ");
    Serial.print(raw);
    Serial.println(" cm");
  }

  int valueToUse = raw;
  if (useMedian) {
    medFilter.push(raw);
    int med = medFilter.median();
    // med puede ser -1 si todas inválidas
    valueToUse = med;
  }

  // Si valueToUse es -1 -> no decidir mover servo
  if (valueToUse != -1) {
    if (valueToUse <= CRITICAL_CM) {
      // caso crítico -> 90°
      door.writeAngle(90);
    } else if (valueToUse <= MEDIUM_CM) {
      // caso medio -> 45°
      door.writeAngle(45);
    } else {
      door.writeAngle(0);
      Serial.println("Rango lejano (>50cm): no cambiar ángulo");
    }
  }

  delay(LOOP_DELAY_MS);
}