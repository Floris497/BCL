//
//  BCLObjects.h
//  Basic Control Layer
//
//  Created by Floris Fredrikze on 15/11/14.
//  Copyright (c) 2014 MiniMind. All rights reserved.
//

#ifndef Basic_Control_Layer_BCLObjects_h
#define Basic_Control_Layer_BCLObjects_h

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <errno.h>
//#include "rpiGpio.h"
//#include <wiringPi.h>

#define kMaxSpeedValue 1023
#define kMotorDualSideCommand 7
#define kMotorBoardID 0x32

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
    unsigned int commandLength;
} I2CData;

typedef struct I2CCommand {
    I2CDevice device;
    I2CData data;
    kI2CMode mode;
} I2CCommand;

typedef int BCLSocket;

#endif
