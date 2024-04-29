#include "motor_functions.h"

// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 


#include <Wire.h>
  
// Motor A

int enA = 6; //9 DOesnt work for my uno for some reason
int in1 = 8;
int in2 = 7;

// Motor B

int enB = 3;
int in3 = 10;
int in4 = 9;

// Define output strings

String str_gForceX;
String str_gForceY;
String str_out;
float gForceX, gForceY;

int gForceX_speed,gForceY_speed;

// Motor Speed Values - Start at zero

int MotorSpeed1 = 0;
int MotorSpeed2 = 0;
int MotorSpeed[2] = {1,1};
int nullArr[2] = {0, 0};


// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

void setup()
{
  // Set all the motor control pins to outputs
  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
   
  // Start with motors disabled and direction forward
  
  // Motor A
  
  digitalWrite(enA, LOW);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  // Motor B
  
  digitalWrite(enB, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
  // Initialize ASK Object
  rf_driver.init();
  // Setup Serial Monitor
  Serial.begin(9600);
}


void loop()
{
    // Set buffer to size of expected message
    uint8_t buf[10];
    uint8_t buflen = sizeof(buf);
    // Check if received packet is correct size
    if (rf_driver.recv(buf, &buflen))
    {
      
      // Message received with valid checksum
      // Get values from string
      
      // Convert received data into string
      str_out = String((char*)buf);
      
      // Split string into two values
      for (int i = 0; i < str_out.length(); i++) 
      {
        if (str_out.substring(i, i+1) == ",") 
          {
        str_gForceX = str_out.substring(0, i);
        str_gForceY = str_out.substring(i+1);
        break;
          }
      }
      gForceX = str_gForceX.toFloat();
      gForceY = str_gForceY.toFloat();
      // Print values to Serial Monitor
      Serial.print("gForceX: ");
      Serial.print(gForceX);
      Serial.print("  - gForceY: ");
      Serial.println(gForceY);
               
    // Determine if this is a forward or backward motion
    // Do this by reading the Verticle Value
    // Apply results to MotorSpeed and to Direction
  
     if (gForceX < -0.4)
     {
      // This is Backward
      moveBackward(in1, in2, in3, in4, MotorSpeed, gForceX);
      MotorSpeed1 = MotorSpeed[0];
      MotorSpeed2 = MotorSpeed[1];   
  //    Serial.print(gForceX_speed);
  //    Serial.print("Backward");
  //    Serial.print(MotorSpeed[0]);
  //    Serial.println(MotorSpeed[1]);
    }
    else if (gForceX > 0.4)
    {
      // This is Forward
      moveForward(in1, in2, in3, in4, MotorSpeed, gForceX);
      MotorSpeed1 = MotorSpeed[0];
      MotorSpeed2 = MotorSpeed[1];   
  
  //    Serial.print(gForceX_speed);
  //    Serial.print("Forward");
  //    Serial.print(MotorSpeed[0]);
  //    Serial.println(MotorSpeed[1]);
          
    }
  
     // Now do the steering
    // The Horizontal position will "weigh" the motor speed
    // Values for each motor
  
    else if (gForceY > 0.4)
    {
      // Move Left
     
      moveLeft(in1, in2, in3, in4, MotorSpeed, gForceX, gForceY);
      MotorSpeed1 = MotorSpeed[0];
      MotorSpeed2 = MotorSpeed[1];   
  //    Serial.print("Left");
  //    Serial.print(MotorSpeed[0]);
  //    Serial.println(MotorSpeed[1]);
      
    }
    
    else if (gForceY < -0.4)
    {
          
      // Move Right
      moveRight(in1, in2, in3, in4, MotorSpeed, gForceX, gForceY);
      MotorSpeed1 = MotorSpeed[0];
      MotorSpeed2 = MotorSpeed[1];   
  //    Serial.print("Right");
  //    Serial.print(MotorSpeed[0]);
  //    Serial.println(MotorSpeed[1]);  
    }
  
    else
    {
      // This is Stopped
  
      MotorSpeed1 = 0;
      MotorSpeed2 = 0; 
  
    }

  }
  
  
  // Adjust to prevent "buzzing" at very low speed
  
  if (MotorSpeed1 < 8)MotorSpeed1 = 0;
  if (MotorSpeed2 < 8)MotorSpeed2 = 0;
  
  // Set the motor speeds

//  Serial.println(MotorSpeed1);
//  Serial.println(MotorSpeed2);
  analogWrite(enA, MotorSpeed1);
  analogWrite(enB, MotorSpeed2);
}
