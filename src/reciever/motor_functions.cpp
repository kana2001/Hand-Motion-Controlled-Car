#include "motor_functions.h"
#include <stdlib.h> 

void moveBackward(int in1, int in2, int in3, int in4, int MotorSpeed[], float gForceX)
{
   // This is Backward

    // Set Motor A backward

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    // Set Motor B backward

    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    //Determine Motor Speeds

   // As we are going backwards we need to reverse readings
    int gForceX_speed;
    gForceX_speed = gForceX * -100 ; // This produces a positive number

    if(gForceX_speed > 100){
      gForceX_speed = 100;
    }
    
    
    MotorSpeed[0] = map(gForceX_speed, 0, 100, 0, 255);
    MotorSpeed[1] = map(gForceX_speed, 0, 100, 0, 255);
}

void moveForward(int in1, int in2, int in3, int in4, int MotorSpeed[], float gForceX)
{
   // This is forward

    // Set Motor A forward

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    // Set Motor B forward

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    //Determine Motor Speeds
    
    int gForceX_speed;
    gForceX_speed = gForceX * 100; 

    if(gForceX_speed > 100){
      gForceX_speed = 100;
    }
    
    
    MotorSpeed[0] = map(gForceX_speed, 0, 100, 0, 255);
    MotorSpeed[1] = map(gForceX_speed, 0, 100, 0, 255);
}

void moveLeft(int in1, int in2, int in3, int in4, int MotorSpeed[], float gForceX, float gForceY)
{
    // Move Left

    int *tempArray = (int*) malloc(2*sizeof(int));
    *tempArray = 0;
    *(tempArray + 1) = 0;
//    //Determine if the car should move forward or backward
//    if (gForceX < 0){
//       moveBackward(in1, in2, in3, in4, tempArray, 0); 
//    }
//    else{
    moveForward(in1, in2, in3, in4, tempArray, 0);
//    }
    free(tempArray);

    
    //Convert the float reading for gForceY into an int that ranges from 0 to 100
    int gForceY_speed;
    
    gForceY_speed = gForceY * 100;

    // Map the number to a value of 255 maximum
    
    gForceY_speed = map(gForceY_speed, 0, 100, 0, 255);
    Serial.println("Left");
    MotorSpeed[0] = MotorSpeed[0] + gForceY_speed;
    MotorSpeed[1] = MotorSpeed[1] - gForceY_speed;

    // Don't exceed range of 0-255 for motor speeds

    if (MotorSpeed[0] > 255)MotorSpeed[0] = 255;
    if (MotorSpeed[1] < 0)MotorSpeed[1] = 0;  
    

}

void moveRight(int in1, int in2, int in3, int in4, int MotorSpeed[], float gForceX, float gForceY)
{
    // Move Right

    int *tempArray = (int*) malloc(2*sizeof(int));
    *tempArray = 0;
    *(tempArray + 1) = 0;
    //Determine if the car should move forward or backward
//    if (gForceX < 0){
//       moveBackward(in1, in2, in3, in4, tempArray, 0); 
//    }
//    else{
    moveForward(in1, in2, in3, in4, tempArray, 0);
//    }
    free(tempArray);

    
    //Convert the float reading for gForceY into an int that ranges from 0 to 100
    int gForceY_speed;
    
    // Move Right
    //Convert the float reading for gForceY into an int that ranges from 0 to 100
    gForceY_speed = gForceY * -100;

    // Map the number to a value of 255 maximum
    
    gForceY_speed = map(gForceY_speed, 0, 100, 0, 255);
    Serial.println("Right");
    MotorSpeed[0] = MotorSpeed[0] - gForceY_speed;
    MotorSpeed[1] = MotorSpeed[1] + gForceY_speed;
 
    // Don't exceed range of 0-255 for motor speeds
  
    if (MotorSpeed[0] < 0)MotorSpeed[0] = 0;
    if (MotorSpeed[1] > 255)MotorSpeed[1] = 255;

}
