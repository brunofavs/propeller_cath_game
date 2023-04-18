#include <stdio.h>
#include "simpletools.h"
#include "servo.h"
#include "ping.h"

// -----------------------------------------
//            GLOBAL VARIABLES / Defines
// -----------------------------------------

#define LEFT_WHEEL  12
#define RIGHT_WHEEL 13 // This wheel is inversed, giving positive speed makes it go backwards.

#define LEFT_SENSOR_PIN 9
#define RIGHT_SENSOR_PIN 8

//! Making these global variables so that I can acess them both inside the callback and main functions
//! I dont know to to implement partials like in functools from python in C
// Also initializing both to 0 incase the program gets to the logic in main b4 the callback has processed the first set of data
int delta_distance_left = 0;
int delta_distance_right = 0;

int turning_speed = 50;
int straigth_speed = 50;
// -----------------------------------------
//            Function definitions
// -----------------------------------------

void propellerConfig(){
  set_direction(11,1);
}

void rotateLeft(){
  //servo_speed accepts inputs from -100 to 100
  servo_speed(RIGHT_WHEEL ,turning_speed);
  servo_speed(LEFT_WHEEL ,turning_speed);
  printf("Rotating left\n");
}

void rotateRigth(){
  servo_speed(RIGHT_WHEEL,-turning_speed);
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

//! This function should be computing the distance every time so that when the robot needs it to acess directions it has the most recent updates
void computeDistances(){
  while(1){
    int first_left = ping_cm(LEFT_SENSOR_PIN); // Measure left sensor
    int first_right = ping_cm(RIGHT_SENSOR_PIN); // Measure right sensor

    pause(100);   // Pause 100ms                     

    delta_distance_left = ping_cm(LEFT_SENSOR_PIN) - first_left;
    delta_distance_right = ping_cm(RIGHT_SENSOR_PIN) - first_right;
    
    //? For some reason measuring at runtime doesn't work xd
    // printf("\n\nActual distance right is %d\n",ping_cm(RIGHT_SENSOR_PIN));

    // printf("\n\nActual distance right is %d\n",first_right);
    printf("\nDelta distance right is %d\n",delta_distance_right);
  }
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
    pause(100);   // Pause 10ms                     
  }  
}
