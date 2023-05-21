
#ifndef Display4_h//if motor class is not yet defined
#define Display4_h// defne motr class
#include <Arduino.h>//include arduino default library
class SevSeg {//define car class andits properties and methods
private:
//only available inside the class
int D1;
int D2;
int D3;
int D4;
int latch;
int clock;
int data;
public:// available outside class
SevSeg();//car class overload
SevSeg(int D1, int D2, int D3, int D4, int latch, int clock, int data);
void display(int x, int y, int z, int a);
void init();// method for initializing car class

};
#endif
