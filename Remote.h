#include <IRremote.hpp>

#ifndef Remote_h//if motor class is not yet defined
#define Remote_h// defne motr class

#define IR_RECEIVE_PIN 9

unsigned long res;
unsigned long fres;
String button;
int delta;
int modul=0;
int a;
int x;
int y;
int z;
void RemRun(){
  
 if (IrReceiver.decode()) {
    res = IrReceiver.decodedIRData.decodedRawData; // Print "old" raw data
      IrReceiver.resume(); // Enable receiving of the next value
  }
  
  if(res!= 0 && res!=fres){

fres= res;
Serial.println(fres);
switch (fres) {       // if results.value is equal to....
      case 3125149440:               // the On/off button then...
        Serial.println("ON/OFF");  // serial print on/ off
      button = "ON/OFF";
        break;
      case 4061003520:             // the rept button
        Serial.println("REPT");  // serial print rept   
         button = "REPT";// set toggle equal to 1
        break;
      case 3860463360:           // the EQ button
        Serial.println("EQ");  // serial print EQ
        button = "EQ";
        break;
      case 3910598400:
        Serial.println("0");
        delta = 0;
        modul++;
        break;
      case 4077715200:
        Serial.println("1");
      delta = 1;
      modul++;
        break;
      case 3877175040:
        Serial.println("2");
        delta = 2;
        modul++;
        break;
      case 2707357440:
        Serial.println("3");
        delta = 3;
        modul++;
        break;
      case 4144561920:
        Serial.println("4");
        delta = 4;
        modul++;
        break;
      case 3810328320:
        Serial.println("5");
        delta = 5;
        modul++;
        break;
      case 2774204160:
      Serial.println("6");
        delta = 6;
        modul++;
        break;
      case 3175284480:
        Serial.println("7");
        delta = 7;
        modul++;
        break;
      case 2907897600:
        Serial.println("8");
          delta = 8;
          modul++;
        break;
      case 3041591040:
        Serial.println("9");
        delta = 9;
        modul++;
        break;
         case 3208707840:
        Serial.println("play");
        button = "PLAY";
  fres=0;
  res=0;
          modul++;
        break;   // if results.value is equal to....
      case 3108437760:             //the VOL + button then...
        Serial.println("VOL+");  // Serial print Vol +
        button = "VOL+";
         // bool r is equal to 0
        break;

      case 3141861120:            //the |<< button then...
        Serial.println("|<<");  // Serial print |<< 
        button = "|<<";                 // bool r is equal to 0
        break;

      case 3158572800:            //the >>| button then...
        Serial.println(">>|");  // Serial print >>|
        button = ">>|";                  // bool r is equal to 1
        break;

      case 3927310080:             //the VOL + button then...
        Serial.println("VOL-");  // Serial print Vol -
            button = "VOL-";           // bool r is equal to 0
        break;

      case 4127850240:
        Serial.println("^^");
        button = "^^";

        break;  
    case 4161273600:
        Serial.println("vv");
        button = "vv";
       
        break; 
}}

if (modul != 0) {
    if (modul % 4 == 0) {
      x = delta;
    }
    if (modul % 4 == 1) {
      y = delta;
    }
    if (modul % 4 == 2) {
      z = delta;
    }
    if (modul % 4 == 3) {
      a = delta;
    }
  }
}
#endif
