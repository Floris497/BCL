//
//  header.h
//  Basic Control Layer
//
//  Created by Floris Fredrikze on 01/10/14.
//  Copyright (c) 2014 MiniMind. All rights reserved.
//

#ifndef Basic_Control_Layer_header_h
#define Basic_Control_Layer_header_h


typedef struct I2CDevice {
    uint8_t  I2C_ID;
} I2CDevice;

typedef struct I2CData {
    I2CDevice device;
    uint8_t command[10];
    uint8_t commandLength;
} I2CData;

enum {
    I2C_SEND_MODE,
    I2C_RECIEVE_MODE
};

// ---- script layer ---- //




// ---- access layer ---- //
int moveForwardWithSpeed(uint8_t speed); //1 to 100
int moveBackwardWithSpeed(uint8_t speed); //1 to 100
int moveLeftWithSpeedAndIntensity(uint8_t speed,uint8_t intensity); // both 1 to 100
int moveRightWithSpeedAndIntensity(uint8_t speed,uint8_t intensity); // both 1 to 100
int turnRight();
int turnLeft();
int turnLeftDegrees(int degrees); // can move more rounds
int turnRightDegrees(int degrees); // can more more rounds
int stopCarInTime(int Seconds);


// ---- module layer ---- //
int stopCar();
int moveWithSpeed(int leftSpeed,int rightSpeed);
int getDirection(); // return negative ERROR
int getDistance();

// ---- support layer ---- //
int makeCommandFromSpeed(int leftSpeed,int rightSpeed,I2CData data);
int sendI2CCommand(I2CData data);
I2CData getI2CData(I2CData data);


// ---- I2C Manager ---- //
void I2CTask(I2CData data,int I2C_MODE);


#endif
