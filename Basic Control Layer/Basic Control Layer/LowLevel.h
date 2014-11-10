//
//  LowLevel.h
//  Basic Control Layer
//
//  Created by Floris Fredrikze on 18/10/14.
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



#ifndef __Basic_Control_Layer__LowLevel__
#define __Basic_Control_Layer__LowLevel__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
//#include "rpiGpio.h"
//#include <wiringPi.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <poll.h>
#include <errno.h>
#include <arpa/inet.h>

#define kMaxSpeedValue 1023
#define kMotorDualSideCommand 7

typedef enum kWheelDirection {
    kWheelDirectionNoDirection,
    kWheelDirectionForwards,
    kWheelDirectionBackwards
} kWheelDirection;

typedef struct BCLWheel {
    uint16_t speed;
    kWheelDirection direction;
} BCLWheel ;

typedef enum kI2CMode {
    kI2CModeSend,
    kI2CModeRecieve
} kI2CMode;

typedef struct I2CDevice {
    uint8_t  I2C_ID;
} I2CDevice;

typedef struct I2CData {
    uint8_t command[10];
    unsigned int commandLength;
} I2CData;

typedef struct I2CCommand {
    I2CDevice device;
    I2CData data;
    kI2CMode mode;
} I2CCommand;

typedef int BCLSocket;

#pragma mark - I2C Manager
I2CData I2CTask(I2CCommand command);


#pragma mark - Support Functions
BCLWheel getBCLWheelFromSpeed(int speed,int maxSpeed);


#pragma mark - Low Level Support Functions
unsigned int maxSpeedCheck(unsigned int speed,unsigned int max);
uint8_t getHigh8bits(uint16_t number);
uint8_t getLow8bits(uint16_t number);
void BCLLog(char* msg);
void BCLError(char *msg);


#endif /* defined(__Basic_Control_Layer__LowLevel__) */




