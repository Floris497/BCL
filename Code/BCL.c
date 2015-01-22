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

#pragma mark - Module Layer

// Initialiseerd alles voor de robot
int init() {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    initRaspberryConnections();
    return 0;
}

// synoniem voor 'pthread_join'
int joinThread(pthread_t thread) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    return pthread_join(thread, NULL);
}

// synoniem voor 'pthread_cancel'
int stopThread(pthread_t thread) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    stopMotors();
    return pthread_cancel(thread);
}

// stopt de motoren
int stopMotors() {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    // stuurt een snelheid van 0 0 naar de motoren
    moveWithSpeed(0, 0);
    return 0;
}

// laat de motoren draaien voor een gegeven snelheid van links en rechts
int moveWithSpeed(int leftSpeed,int rightSpeed) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    
    // maakt een I2C command aan
    I2CCommand command;
    // laad een I2CData object in voor de geven snelheid
    command.data = makeI2CDataFromSpeed(leftSpeed, rightSpeed);
    // geeft aan wat het device id van het motor board is
    command.device = kMotorBoardID;
    // geeft aan dat het via I2C verzonden moet worden
    command.mode = kI2CModeSend;
    
    // stuurd het I2C Command door naar de I2C manager
    I2CTask(command);
    
    return 0;
}

int getDistanceToObject(){
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);

    I2CData sendOne,sendTwo,distanceReturnData;
    
    sendOne.command = malloc(2);
    sendOne.commandLength = 2;
    sendOne.command[0] = 0x00;
    sendOne.command[1] = 0x51;
    
    sendTwo.command = malloc(1);
    sendTwo.commandLength = 1;
    sendTwo.command[0] = 0x31;
    
    sendI2CCommand(sendOne,kDistanceSensorID);
    usleep(100);
    sendI2CCommand(sendTwo,kDistanceSensorID);
    usleep(100);
    
    distanceReturnData = getI2CData(1, kDistanceSensorID);

    int distance = distanceReturnData.command[0];

    free(sendOne.command);
    free(sendTwo.command);
    free(distanceReturnData.command);

    printf("Distance %i \n", distance);
    return distance;

}

double getDistanceTraveled(int wheelCounter) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    return (((double)wheelCounter/kInterruptsPerRotation)*(2.0*M_PI*(kWheelDiameter/2.0))*100);
}

int getCompassValue() {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    I2CData setPointer, compassReturnData;
    int16_t values[3] = {0, 0, 0};


    setPointer.command = malloc(1);
    setPointer.commandLength = 1;
    setPointer.command[0] = kCompassDataReg;

    sendI2CCommand(setPointer, kCompassID);

    compassReturnData = getI2CData(6, kCompassID);

    values[0] = (compassReturnData.command[0]<<8) | compassReturnData.command[1]; //x
    values[1] = (compassReturnData.command[2]<<8) | compassReturnData.command[3]; //z
    values[2] = (compassReturnData.command[4]<<8) | compassReturnData.command[5]; //y

    values[2] += 30;

    float bearing;
    bearing = atan2(values[2], values[0]);

    //makes the bearing always positive by adding 2pi to it
    //2 pi = full circle/360 degrees
    if(bearing < 0){
      bearing += 2*M_PI;
    }

    //convert the radial bearing into degrees 
    bearing *= 180/M_PI;

    free(setPointer.command);
    free(compassReturnData.command);

    return bearing;   

}


// opend socket op 'port'
BCLSocket openSocket(int portNumber, int options){
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    
    // print welke port de socket word geopend
    char *buffer = malloc(100);
    sprintf(buffer,"Opening Socket on port: %d",portNumber);
    BCLLog(buffer,kLogInfo);
    free(buffer);
    
    // socket configuratie
    int sockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0)
       BCLLog("not able to open",kLogFatalError);
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portNumber);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    BCLLog("not able to open",kLogFatalError);
       return 0;
    }

    listen(sockfd,5);
    clilen = sizeof(cli_addr);
  
    BCLLog("Ready for incomming connection",kLogInfo);
    BCLSocket socket = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
    BCLLog("Socket connected",kLogInfo);

    return socket;
}


#pragma mark - Support Layer
// maakt 
I2CData makeI2CDataFromSpeed(int leftSpeed,int rightSpeed){
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    
    I2CData data;
    BCLWheel rightWheel,leftWheel;

    rightWheel = getBCLWheelFromSpeed(rightSpeed, kMaxSpeedValue);
    leftWheel = getBCLWheelFromSpeed(leftSpeed, kMaxSpeedValue);
    
    BCLLog("This working?",kLogMark);
    data.command = malloc(7);
    bzero(data.command, 7);
    data.commandLength = 7;
    data.command[0] = kMotorDualSideCommand;
    data.command[1] = getHigh8bits(leftWheel.speed);
    data.command[2] = getLow8bits(leftWheel.speed);
    data.command[3] = leftWheel.direction;
    data.command[4] = getHigh8bits(rightWheel.speed);
    data.command[5] = getLow8bits(rightWheel.speed);
    data.command[6] = rightWheel.direction;
    
    return data;
}

int sendI2CCommand(I2CData data,uint8_t device) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    I2CCommand command;
    command.data = data;
    command.device = device;
    command.mode = kI2CModeSend;
    data = I2CTask(command);
    return 0;
}

I2CData getI2CData(unsigned int length,uint8_t device) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    I2CCommand command;
    I2CData data;
    data.commandLength = length;
    data.command = malloc(length);
    bzero(data.command,length);
    command.data = data;
    command.device = device;
    command.mode = kI2CModeRecieve;
    data = I2CTask(command);
    return data;
}

