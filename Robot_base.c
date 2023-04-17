#include <stdio.h>
#include "simpletools.h"
#include "servo.h"

#define LEFT_WHEEL  12
#define RIGHT_WHEEL 13 // This wheel is inversed, giving positive speed makes it go backwards.

int max_vel = 100;

void propellerConfig(){
  set_direction(11,1);
}

void rotateLeft(){
  //servo_speed accepts inputs from -100 to 100
  servo_speed(RIGHT_WHEEL ,50);
  servo_speed(LEFT_WHEEL ,50);
  printf("Rotating left");
}

void rotateRigth(){
  servo_speed(RIGHT_WHEEL,-50);
  servo_speed(LEFT_WHEEL,50);
  printf("Rotating right");
}

void moveForward(){
  servo_speed(RIGHT_WHEEL,-50);
  servo_speed(LEFT_WHEEL,50);
  printf("Moving forward");
}

void moveBackward(){
  servo_speed(RIGHT_WHEEL,50);
  servo_speed(LEFT_WHEEL,-50);
  printf("Moving forward");
}



int main()                                    // Main function
{
//  rotateLeft();
  propellerConfig();

  int direction_button_state;
  while(1)
  {
    direction_button_state = get_state(11);
    printf("Direction button state is %d",direction_button_state);

    if(direction_button_state){
      moveForward();
    }
    else if(!direction_button_state){
      moveBackward();
    }



    


    
    
    
  }  
}
