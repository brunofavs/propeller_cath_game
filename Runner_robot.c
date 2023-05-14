#include <stdio.h>
#include "simpletools.h"
#include "servo.h"
#include "ping.h"

#define LEFT_WHEEL  12
#define RIGHT_WHEEL 13 // This wheel is inversed, giving positive speed makes it go backwards.

int turning_speed = 50;
int straigth_speed = 55;

void rotateLeft(){
  //servo_speed accepts inputs from -100 to 100
  servo_speed(RIGHT_WHEEL ,-turning_speed);
  servo_speed(LEFT_WHEEL ,-turning_speed);
  printf("Rotating left\n");
}

void rotateRight(){
  servo_speed(RIGHT_WHEEL,turning_speed);
  servo_speed(LEFT_WHEEL,turning_speed);
  printf("Rotating right\n");
}

void moveForward(){
  servo_speed(RIGHT_WHEEL,-straigth_speed);
  servo_speed(LEFT_WHEEL,straigth_speed);
  printf("Moving forward\n");
}

void moveBackward(){
  servo_speed(RIGHT_WHEEL,straigth_speed);
  servo_speed(LEFT_WHEEL,-straigth_speed);
  printf("Moving forward\n");
}

void stopMoving(){
  servo_speed(RIGHT_WHEEL,0);
  servo_speed(LEFT_WHEEL,0);
  // printf("Stopped moving\n");
}

void moveCircle(){

  servo_speed(RIGHT_WHEEL,0.7*straigth_speed);
  servo_speed(LEFT_WHEEL,-straigth_speed);
  printf("Moving in cirles\n");



}


int main()                                    // Main function
{
  // Add startup code here.

 
  while(1)
  {
  moveCircle();   
  }  
}
