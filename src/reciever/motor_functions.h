#ifndef MOTOR_FUNCTIONS_H
#define MOTOR_FUNCTIONS_H
#include <Arduino.h>

void moveBackward(int in1, int in2, int in3, int in4, int MotorSpeed[], float gForceX);

void moveForward(int in1, int in2, int in3, int in4, int MotorSpeed[], float gForceX);

void moveLeft(int in1, int in2, int in3, int in4, int MotorSpeed[], float gForceX, float gForceY);

void moveRight(int in1, int in2, int in3, int in4, int MotorSpeed[], float gForceX, float gForceY);

#endif
