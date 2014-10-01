//
//  header.h
//  Basic Control Layer
//
//  Created by Floris Fredrikze on 01/10/14.
//  Copyright (c) 2014 MiniMind. All rights reserved.
//

#ifndef Basic_Control_Layer_header_h
#define Basic_Control_Layer_header_h


typedef struct I2CInterface {
    uint8_t  deviceID;
} I2CInterface;


// script layer

// driving
int moveForwardWithSpeed(uint8_t speed); //1 to 100
int moveBackwardWithSpeed(uint8_t speed); //1 to 100
int moveLeftWithSpeedAndIntensity(uint8_t speed,uint8_t intensity); // both 1 to 100
int moveRightWithSpeedAndIntensity(uint8_t speed,uint8_t intensity); // both 1 to 100
int turnRight();
int turnLeft();

// access layer
void moveWithSpeed(int leftSpeed,int rightSpeed);


// module layer
void makeCommandFromSpeed(int leftSpeed,int rightSpeed,int *command);
void sendI2CCommandTo(I2CInterface device,int *command,int length);


// support layer



#endif
