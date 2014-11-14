//
//  BCL.c
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



#include "BCL.h"
#include "BCLParse.h"

#pragma mark - Access Layer


#pragma mark - Module Layer

int init() {
    initRaspberryConnections();
    return 0;
}

int joinThread(pthread_t thread) {
    return pthread_join(thread, NULL);
}

int stopThread(pthread_t thread) {
    stopMotors();
    return pthread_cancel(thread);
}

int stopMotors() {
    moveWithSpeed(0, 0);
    return 0;
}

int moveWithSpeed(int leftSpeed,int rightSpeed) {
    
    I2CData data;
    data = makeI2CDataFromSpeed(leftSpeed, rightSpeed);
    
    I2CDevice device;
    device.I2C_ID = kMotorBoardID;
    
    I2CCommand command;
    command.data = data;
    command.device = device;
    command.mode = kI2CModeSend;
    
    I2CTask(command);
    
    return 0;
}

BCLSocket openSocket(int portNumber, int options){
    
    char *buffer = malloc(100);
    sprintf(buffer,"Opening Socket on port: %d",portNumber);
    BCLMark(buffer);
    
    int sockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0)
       BCLError("not able to open");
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portNumber);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
       BCLError("not able to bind");

    listen(sockfd,5);
    clilen = sizeof(cli_addr);
  
    BCLLog("Ready for incomming connection");
    BCLSocket socket = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
    BCLLog(ANSI_COLOR_GREEN"Socket connected"ANSI_COLOR_RESET);

    return socket;
}


#pragma mark - Support Layer
I2CData makeI2CDataFromSpeed(int leftSpeed,int rightSpeed){
    
    I2CData data;
    BCLWheel rightWheel,leftWheel;

    rightWheel = getBCLWheelFromSpeed(rightSpeed, kMaxSpeedValue);
    leftWheel = getBCLWheelFromSpeed(leftSpeed, kMaxSpeedValue);
    
    char *buffer = malloc(100);
    snprintf(buffer, sizeof(buffer), "DrivingInfo: RS:%d - RD:%d : LS:%d - LD:%d\n",rightWheel.speed,rightWheel.direction,leftWheel.speed,leftWheel.direction);
    BCLMark(buffer);
    
    data.commandLength = 7;
    data.command[0] = kMotorDualSideCommand;
    data.command[1] = getHigh8bits(rightWheel.speed);
    data.command[2] = getLow8bits(rightWheel.speed);
    data.command[3] = rightWheel.direction;
    data.command[4] = getHigh8bits(leftWheel.speed);
    data.command[5] = getLow8bits(leftWheel.speed);
    data.command[6] = leftWheel.direction;
    
    return data;
}

int sendI2CCommand(I2CData data,I2CDevice device) {
    I2CCommand command;
    command.data = data;
    command.device = device;
    command.mode = kI2CModeSend;
    data = I2CTask(command);
    return 0;
}

I2CData getI2CData(I2CData data,I2CDevice device) {
    I2CCommand command;
    command.data = data;
    command.device = device;
    command.mode = kI2CModeRecieve;
    data = I2CTask(command);
    return data;
}




