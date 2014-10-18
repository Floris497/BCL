//
//  header.h
//  Basic Control Layer
//
//  Created by Floris Fredrikze on 01/10/14.
//  Copyright (c) 2014 MiniMind. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.



#ifndef Basic_Control_Layer_header_h
#define Basic_Control_Layer_header_h

#include <stdio.h>

#include "LowLevel.h"

#pragma mark - Script Layer
/*TODO*/ int turnLeftDegrees(int degrees);
/*TODO*/ int turnRightDegrees(int degrees);
/*TODO*/ int stopCarInTime(int Seconds);
/*TODO*/ int moveForwardWithSpeedForTime(int8_t speed,int seconds);
/*TODO*/ int movebackwardsWithSpeedForTime(int8_t speed,int seconds);
/*TODO*/ int moveForwardWithSpeedForDistance(int8_t speed,int meters);
/*TODO*/ int movebackwardsWithSpeedForDistance(int8_t speed,int meters);
/*TODO*/ int getDistanceToWall();
/*TODO*/ int stopCar();

/*TODO*/ void Initialize();

/*TODO*/ int openConnection(int port);


#pragma mark - Access Layer
/*TODO*/ int moveForwardWithSpeed(int8_t speed); //1 to 100
/*TODO*/ int moveBackwardWithSpeed(int8_t speed); //1 to 100
/*TODO*/ int moveLeftWithSpeedAndIntensity(int8_t speed,uint8_t intensity); // both 1 to 100
/*TODO*/ int moveRightWithSpeedAndIntensity(int8_t speed,uint8_t intensity); // both 1 to 100
/*TODO*/ int turnLeft();
/*TODO*/ int turnRight();
/*TODO*/ int getDistanceInDirection(int direction);
/*TODO*/ int makeMotorThread(void* func,pthread_t *thread);
/*TODO*/ int stopMotors();
/*TODO*/ int stopThread();


#pragma mark - Module Layer
/*TODO*/ int moveWithSpeed(int16_t leftSpeed,int16_t rightSpeed);
/*TODO*/ int getDirection(); // return negative ERROR
/*TODO*/ int getDistance();
/*TODO*/ int getDistanceTraveled();
/*TODO*/ int openSocket(int port,int options);


#pragma mark - Support Layer
I2CData makeI2CDataFromSpeed(int16_t leftSpeed,int16_t rightSpeed,I2CData data);
int sendI2CCommand(I2CData data,I2CDevice device);
I2CData getI2CData(I2CData data,I2CDevice device);

int getWheelCounter();
int resetWheelCounter();


#endif




