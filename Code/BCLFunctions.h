//
//  BCLFunctions.h
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



#ifndef __Basic_Control_Layer__BCLFunctions__
#define __Basic_Control_Layer__BCLFunctions__

#include "colors.h"
#include "BCLObjects.h"

#pragma mark - I2C Manager
I2CData I2CTask(I2CCommand command);

#pragma mark - Support Functions
pthread_t startThread(void* func);
int doBackGroundTaskWithCallback(void* callbackFunction);
BCLWheel getBCLWheelFromSpeed(int speed,int maxSpeed);
int initRaspberryConnections();


#pragma mark - Low Level Support Functions
unsigned int maxSpeedCheck(unsigned int speed,unsigned int max);
uint8_t getHigh8bits(uint16_t number);
uint8_t getLow8bits(uint16_t number);

void BCLLog(char *log, kLogType logType);
void BCLMarkFunc(const char *funcNameFull,const char *funcName);
char* substring(const char* str, size_t begin, size_t len);


#endif /* defined(__Basic_Control_Layer__BCLFunctions__) */




