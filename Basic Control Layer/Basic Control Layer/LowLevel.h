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

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define kMaxSpeedValue 1023
#define kMotorDualSideCommand 7

typedef enum kWheelDirection {
    kWheelDirectionNoDirection,
    kWheelDirectionForwards,
    kWheelDirectionBackwards
} kWheelDirection;

typedef enum kI2CMode {
    kI2CModeSend,
    kI2CModeRecieve
} kI2CMode;

typedef struct BCLWheel {
    uint16_t speed;
    kWheelDirection direction;
} BCLWheel ;

typedef struct I2CDevice {
    uint8_t  I2C_ID;
} I2CDevice;

typedef struct I2CData {
    uint8_t command[10];
    uint8_t commandLength;
} I2CData;

typedef struct I2CCommand {
    I2CDevice device;
    I2CData data;
    kI2CMode mode;
} I2CCommand;

#pragma mark - I2C Manager
I2CData I2CTask(I2CCommand command);


#pragma mark - Support Functions
BCLWheel getBCLWheelFromSpeed(int16_t speed,uint16_t maxSpeed);

#pragma mark - Low Level Support Functions
uint16_t maxSpeedCheck(uint16_t speed,uint16_t max);

uint8_t getHigh8bits(uint16_t number);
uint8_t getLow8bits(uint16_t number);


#endif /* defined(__Basic_Control_Layer__LowLevel__) */




