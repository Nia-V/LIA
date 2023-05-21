/*
Goal: interface for car class
Themes: class
*/

#ifndef Motorclass_h//if motor class is not yet defined
#define Motorclass_h// defne motr class
#include <Arduino.h>//include arduino default library
class Car {//define car class andits properties and methods
private://only available inside the class
int speed;//speed property 
public:// available outside class
Car(){};//car class overload
void init();// method for initializing car class
void Forwards(int speed);//forward method
void Backwards(int speed);//backwards method
void Left(int speed);//left method
void Right(int speed);//right method
void STOP();// stop method
};
#endif