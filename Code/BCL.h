//
//  BCL.h
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
#include "BCLObjects.h"
#include "BCLExecute.h"

#pragma mark - Module Layer
int init();
pthread_t startThread(void* func);
int stopThread(pthread_t thread);
int joinThread(pthread_t thread);
int stopMotors();
int moveWithSpeed(int leftSpeed,int rightSpeed);
/*TODO*/ int getDirection();
int getDistanceToObject();
double getDistanceTraveled(int wheelCounter);
int getCompassValue();
BCLSocket openSocket(int portNumber,int options);


#pragma mark - Support Layer
I2CData makeI2CDataFromSpeed(int leftSpeed,int rightSpeed);
int sendI2CCommand(I2CData data,uint8_t device);
I2CData getI2CData(unsigned int length,uint8_t device);

int getWheelCounter();
int resetWheelCounter();

#endif


