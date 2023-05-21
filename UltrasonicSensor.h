#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H
#include "MotorClass.h"
#include <NewPing.h>
#include <Servo.h>

class UltrasonicSensor {
private:
  NewPing sensor;                     // NewPing object for the ultrasonic sensor
  unsigned long lastMeasurementTime;  // Time of the last distance measurement

  // Delay between measurements to avoid false readings (in milliseconds)
  const unsigned long measurementInterval = 100;

public:

  Servo myServo2;
  Car myCar2;
  // Constructor
  UltrasonicSensor(uint8_t trigPin, uint8_t echoPin, unsigned int maxDistance);

  // Function to measure the distance and return it
  unsigned int getDistance();

  // Function to check if the distance is less than or equal to a specific value
  bool isDistanceLessThanOrEqual(unsigned int threshold);

  void init();
};

#endif  // ULTRASONICSENSOR_H
