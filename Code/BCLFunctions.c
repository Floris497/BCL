//
//  BCLFunctions.c
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



#include "BCLFunctions.h"

pthread_mutex_t I2CMutex = PTHREAD_MUTEX_INITIALIZER;
I2CDevice lastDevice;


#pragma mark - I2C Manager
I2CData I2CTask(I2CCommand command) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    // Lock function so I2C is not used twise at a time
    BCLMark("I2C Task Executed");
    pthread_mutex_lock(&I2CMutex);
    // Set 7bit slave for communication with the right device
    
    if (lastDevice.I2C_ID != command.device.I2C_ID) {
        gpioI2cSet7BitSlave(command.device.I2C_ID);
    }
    else {
        lastDevice.I2C_ID = command.device.I2C_ID;
    }
    
    // Determine if data must be send or recieved
    if (command.mode == kI2CModeSend) {
        //Send data to device
        gpioI2cWriteData(command.data.command,command.data.commandLength);
    }
    else if (command.mode == kI2CModeRecieve) {
        // Read from device
        gpioI2cReadData(command.data.command,command.data.commandLength);
    }
    else {
        BCLError("wrong mode specified");
    }
    // It is now safe to unlock the function
    pthread_mutex_unlock(&I2CMutex);
    BCLMark("I2C Task Done");

    // Return I2CData
    return command.data;
}

#pragma mark - Support Functions

pthread_t startThread(void* func) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    pthread_t tid;
    pthread_create(&tid, NULL, func, NULL);
    return tid;
}

int doBackGroundTaskWithCallback(void* callbackFunction) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    startThread(callbackFunction);
    return 0;
}

BCLWheel getBCLWheelFromSpeed(int speed,int maxSpeed) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
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
    wheel.speed = maxSpeedCheck((unsigned int)abs(speed), maxSpeed);
    
    return wheel;
}

int initRaspberryConnections() {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    uint8_t totalPower[2] = {4,255}; // command to set glabal power to 255 (4: command to set glabal power)
    uint8_t softStart[3] = {0x91,23,0}; // command to turn off "DC softstart"? (EEPROM addres 23 to 0) (0x91: command to change EEPROM)
    
    BCLMark("Init Connections Started");

    if (gpioSetup()!= OK) {
        BCLError("gpio setup Failed");
    }
    if (gpioI2cSetup() != OK) {
        BCLError("I2C setup Failed");
    }
    if (gpioI2cSet7BitSlave(0x32) != OK) {
        BCLError("gpioI2cSet7BitSlave failed");
    }
    if (gpioI2cWriteData(&totalPower[0], 2) != OK) {
        BCLError("gpioI2cWriteData failed");
    }
    if (gpioI2cWriteData(&softStart[0],3) != OK) {
        BCLError("gpioI2cWriteData failed");
    }
    
    BCLMark("Init Connections Ended");
    return 0;
}

#pragma mark - Low Level Support Functions
unsigned int maxSpeedCheck(unsigned int speed,unsigned int max) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    return (speed > max) ? max : speed;
}

uint8_t getHigh8bits(uint16_t number) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    return number >> 8;
}

uint8_t getLow8bits(uint16_t number) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    return number &  0xFF;
}

void BCLLog(char* log){
    printf("Log: %s\n",log);
    fflush(stdout);
}

void BCLError(char *err) {
    printf(ANSI_COLOR_RED "Error: %s" ANSI_COLOR_RESET "\n",err);
    fflush(stdout);
}

void BCLMark(char *mark) {
    printf(ANSI_COLOR_YELLOW "Mark: %s" ANSI_COLOR_RESET "\n",mark);
    fflush(stdout);
}

void BCLMarkFunc(const char *funcNameFull,const char *funcName) {
    printf(ANSI_COLOR_CYAN "Func: %s" ANSI_COLOR_RESET "\n",funcName);
    fflush(stdout);
}

char* substring(const char* str, size_t begin, size_t len) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len))
        return 0;
    return strndup(str + begin, len);
}




