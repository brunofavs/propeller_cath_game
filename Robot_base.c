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
int delta_dist_left = 0;
int delta_dist_right = 0;

int turning_speed = 50;
int straigth_speed = 100;

// This controls how much the delta_distance has to be for the robot to take action
int min_assess_thresh = 50;
// -----------------------------------------
//            Function definitions
// -----------------------------------------

void propellerConfig(){
  set_direction(11,1);
}

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

int abs(int a){
  return a>0?a:-a;
}

//! This function should be computing the distance every time so that when the robot needs it to acess directions it has the most recent updates
void computeDistances(){
  // The callback has to be in a loop otherwise in runs once and the core gets shut down
  while(1){
    int first_left = ping_cm(LEFT_SENSOR_PIN); // Measure left sensor
    int first_right = ping_cm(RIGHT_SENSOR_PIN); // Measure right sensor

    pause(10);   // Pause 10ms                     
    

    delta_dist_left = ping_cm(LEFT_SENSOR_PIN) - first_left;
    delta_dist_right = ping_cm(RIGHT_SENSOR_PIN) - first_right;
    
    //? For some reason measuring at runtime doesn't work xd
    // printf("\n\nActual distance left is %d\n",first_left);
    // printf("Actual distance right is %d\n",first_right);

    printf("\nDelta distance right is %d\n",delta_dist_right);
    printf("Delta distance left is %d\n",delta_dist_left);
  }
}

int targetAssessing(){
  /*
    This function should assess based on the differential measures whether to turn right or left or keep moving forward
  0- Go forward
  1 - Go left
  2 - Go right
  */  

  //! First the function should assure the car is stopped before reading the distance measures
  stopMoving();

  pause(100); // To assure correct reading

  //! Target going away or torwards the robot(5)
  if(abs(delta_dist_left) > min_assess_thresh && abs(delta_dist_right) > min_assess_thresh){
    printf("Case 5, Forward\n");
    return 0; //! Move forward
  }

  //! Target approaching from out of range to the left (1)
  else if(delta_dist_left < -min_assess_thresh && abs(delta_dist_right)<min_assess_thresh)
  {
    printf("Case 1, Right\n");
    return 2; //! Move right
  }
  
  //! Target approaching from out of range to the right (2)
  else if(delta_dist_right < -min_assess_thresh && abs(delta_dist_left)<min_assess_thresh)
  {
    printf("Case 2, Left\n");
    return 1; //! Move left
  }

  //! Target leaving from being detected on the left sensor to out of range("3")
  else if(delta_dist_left > min_assess_thresh && abs(delta_dist_right)<min_assess_thresh)
  {
    printf("Case 3, Left\n");
    return 1; //! Move left
  }

  //! Target leaving from being detected on the right sensor to out of range("4")
  else if(delta_dist_right > min_assess_thresh && abs(delta_dist_left)<min_assess_thresh)
  {
    printf("Case 4, Right\n");
    return 2; //! Move right
  }
  else{
    return -1; //! Nothing
  }
  
}

void chaseTarget(int direction){
  /*
    This function should give orders to the servos to chase the target based on the output of the targetAssessing function
  0- Go forward
  1 - Go left
  2 - Go right
  */

  int rotating_time = 1000;

  if(direction == 0){
    moveForward();
  }
  else if (direction == 1)
  {
    rotateLeft();
    pause(rotating_time);
    moveForward();
  }
  else if (direction == 2)
  {
    rotateRight();
    pause(rotating_time);
    moveForward();
  }
}


// -----------------------------------------
//            Main function
// -----------------------------------------

int main()                                    // Main function
{
  propellerConfig();

  cog_run(computeDistances,256);

  while(1)
  {

    int direction = targetAssessing();

    chaseTarget(direction);

    // printf("\nDelta distance right is %d\n",delta_dist_right);
    // printf("Delta distance left is %d\n",delta_dist_left);
    

    pause(3000);




  }  
}
//For some godass reason having cog run activated messes with sensor reading wtf 