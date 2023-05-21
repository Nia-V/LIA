#ifndef master_h
#define master_h



#include <Wire.h>
#include <wiring_private.h>

void digitalWrite(int pin, bool value);
void pinMode(int pin, int MODE);
void analogWrite(int pin, int value);
int digitalRead(int pin);
int analogRead(int pin);

#endif