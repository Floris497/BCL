//
//  LowLevel.c
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



#include "LowLevel.h"

pthread_mutex_t I2CMutex = PTHREAD_MUTEX_INITIALIZER;

#pragma mark - I2C Manager
I2CData I2CTask(I2CCommand command) {
    // Lock function so I2C is not used twise at a time
    pthread_mutex_lock(&I2CMutex);
    
    // Set 7bit slave for communication with the right device
    gpioI2cSet7BitSlave(command.device);
    
    // Determine if data must be send or recieved
    if (command.mode == kI2CModeSend) {
        // Send data to device
        gpioI2cWriteData(command.data.command,command.data.commandLength);
    }
    else if (command.mode == kI2CModeRecieve) {
        // Read from device
        gpioI2cReadData(&command.data.command,command.data.commandLength);
    }
    else {
        printf("ERROR: wrong mode specified");
    }
    // It is now safe to unlock the function
    pthread_mutex_unlock(&I2CMutex);
    
    // Return I2CData
    return command.data;
}

#pragma mark - Support Functions
BCLWheel getBCLWheelFromSpeed(int speed,int maxSpeed) {
    BCLWheel wheel;
    
    if (speed < 0) {
        wheel.direction = kWheelDirectionBackwards;
    } else if (speed > 0){
        wheel.direction = kWheelDirectionForwards;
    }
    else {
        wheel.direction = kWheelDirectionNoDirection;
    }
    
    // int abs(int i) Makes/Leaves i positive
    wheel.speed = maxSpeedCheck((uint8_t)abs(speed), maxSpeed);
    
    return wheel;
}

#pragma mark - Low Level Support Functions
unsigned int maxSpeedCheck(unsigned int speed,unsigned int max) {
    return (speed > max) ? max : speed;
}

uint8_t getHigh8bits(uint16_t number) {
    return number >> 8;
}

uint8_t getLow8bits(uint16_t number) {
    return number &  0xFF;
}



