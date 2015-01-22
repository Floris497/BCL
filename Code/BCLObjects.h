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
#ifdef __LP64__
    //64-bit Intel or PPC
#else
    #include "rpiGpio.h"
    #include <wiringPi.h>
#endif


#define kMaxSpeedValue          1023
#define kMotorDualSideCommand   7
#define kMotorBoardID           0x32

#define kDistanceSensorID       0x70

#define kCompassSensorID        0x1E
#define kCompassID              0x1E


#define kCompassConfigRegA      0x00
#define kCompassConfigRegB      0x01
#define kCompassModeReg         0x02
#define kCompassDataReg         0x03 

#define kInterruptsPerRotation  40
#define kWheelDiameter          0.06

typedef enum kWheelDirection {
    kWheelDirectionNoDirection,
    kWheelDirectionBackwards,
    kWheelDirectionForwards
} kWheelDirection;

typedef enum kLogType {
    kLogError, // used for errors
    kLogFatalError, // used for errors
    kLogWarning, // used for warnigns
    kLogInfo, // used for howing some info
    kLogMark, // used to mark a place in the code
    kLogDebug, // used to output debug info
} kLogType;

typedef enum kI2CMode {
    kI2CModeSend,
    kI2CModeRecieve
} kI2CMode;

typedef struct BCLWheel {
    uint16_t speed;
    kWheelDirection direction;
} BCLWheel ;

typedef struct I2CData {
    uint8_t *command;
    unsigned int commandLength;
} I2CData;

typedef struct I2CCommand {
    uint8_t device;
    I2CData data;
    kI2CMode mode;
} I2CCommand;

typedef int BCLSocket;

#endif
