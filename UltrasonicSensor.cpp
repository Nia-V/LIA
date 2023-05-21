#include "UltrasonicSensor.h"

void UltrasonicSensor::init(){

 myServo2.attach(11);

}



UltrasonicSensor::UltrasonicSensor(uint8_t trigPin, uint8_t echoPin, unsigned int maxDistance)
    : sensor(trigPin, echoPin, maxDistance) {
  lastMeasurementTime = 0;

}

unsigned int UltrasonicSensor::getDistance() {
  unsigned long currentTime = millis();

  // Perform measurement only if enough time has passed
  if (currentTime - lastMeasurementTime >= measurementInterval) {
   unsigned int duration = sensor.ping_median(5);
    unsigned int distance = (duration / 2) * 0.0343;
    lastMeasurementTime = currentTime;
    return distance;
  }
  return 10000;

}

bool UltrasonicSensor::isDistanceLessThanOrEqual(unsigned int threshold) {
  unsigned int distance = getDistance();
  Serial.println(distance);
  if (distance <= threshold && distance != 0) {
    return true;
  }
  return false;
}
