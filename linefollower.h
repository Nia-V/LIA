#include "Motorclass.h" 

 
 
void linefollower(){
 
int nowtime;
unsigned long lasttime = 0;
int right;
int left;
int middle;
middle = analogRead(A1);
right =analogRead(A0);
left = analogRead(A2);
  nowtime = millis();
if (nowtime - lasttime >= 1000){
  lasttime = nowtime;


if(middle - right >= 10  && middle - left >= 10){
  robo.Forwards(90);
}
if(right - middle >= 10 && right- left>= 10){
robo.Right(90);
}
if(left- middle>= 10 && left - right>=10 ){
robo.Left(90);
}

}