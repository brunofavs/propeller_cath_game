#include <stdio.h>
#include "simpletools.h"
#include "servo.h"
#include "ping.h"

// -----------------------------------------
//            GLOBAL VARIABLES / Defines
// -----------------------------------------

#define LEFT_WHEEL  12
#define RIGHT_WHEEL 13 // This wheel is inversed, giving positive speed makes it go backwards.

#define LEFT_SENSOR_PIN 15
#define RIGHT_SENSOR_PIN 14

//! Making these global variables so that I can acess them both inside the callback and main functions
//! I dont know to to implement partials like in functools from python in C
//* Also initializing both to 0 incase the program gets to the logic in main b4 the callback has processed the first set of data
int delta_distance_left = 0;
int delta_distance_right = 0;

// -----------------------------------------
//            Function definitions
// -----------------------------------------

void propellerConfig(){
  set_direction(11,1);
}

void rotateLeft(){
  //servo_speed accepts inputs from -100 to 100
  servo_speed(RIGHT_WHEEL ,50);
  servo_speed(LEFT_WHEEL ,50);
  printf("Rotating left\n");
}

void rotateRigth(){
  servo_speed(RIGHT_WHEEL,-50);
  servo_speed(LEFT_WHEEL,50);
  printf("Rotating right\n");
}

void moveForward(){
  servo_speed(RIGHT_WHEEL,-50);
  servo_speed(LEFT_WHEEL,50);
  printf("Moving forward\n");
}

void moveBackward(){
  servo_speed(RIGHT_WHEEL,50);
  servo_speed(LEFT_WHEEL,-50);
  printf("Moving forward\n");
}

//! This function should be computing the distance every time so that when the robot needs it to acess directions it has the most recent updates
void computeDistances(){
  
  int first_left = ping_cm(LEFT_SENSOR_PIN); // Measure left sensor
  int first_right = ping_cm(RIGHT_SENSOR_PIN); // Measure right sensor

  pause(100);   // Pause 100ms                     

  delta_distance_left = ping(LEFT_SENSOR_PIN) - first_left;
  delta_distance_right = ping(RIGHT_SENSOR_PIN) - first_right;
}


// -----------------------------------------
//            Main function
// -----------------------------------------

int main()                                    // Main function
{
  propellerConfig();

  cog_run(computeDistances,128);

  int direction_button_state = 10;
  while(1)
  {
    // direction_button_state = get_state(11);
    // printf("Direction button state is %d",direction_button_state);

    // if(direction_button_state){
    //   moveForward();
    // }
    // else if(!direction_button_state){
    //   moveBackward();
    // }
  }  
}
