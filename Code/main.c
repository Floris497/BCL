//
//  main.c
//  BCL-Test
//
//  Created by Floris Fredrikze on 13/11/14.
//  Copyright (c) 2014 Floris Fredrikze. All rights reserved.
//

#include <stdio.h>
#include "BCL.h"

int lSpeed = 0,rSpeed = 0, change = 0;
int port = 0;
int stop = 0;
int wheelCounter = 0;
int speed = 0;
int bearing = 0;


void wheelInterruptHandler();
void socketListen(BCLSocket sockfd);

// Thread Main functions
void *motorMain();
void *distanceSensorMain();
void *wheelSensorMain();
void *speedMain();
void *compassMain();
void *socketMain();

// Function to send message over socket
void *answerRequest(BCLSocket sockfd, kBCLMessageType type);
int getObjectData(void *obj);

// Main robot function
// program takes socket port as input
int main(int argc, const char * argv[]) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    if (argc > 1) {
        BCLLog("argc is bigger than 1",kLogDebug);
        port = atoi(argv[1]);
    }
    
    BCLLog("Program Started",kLogMark);
    // initialisation of all the hard- and software
    init();
    
    pthread_t motorThread = startThread(motorMain);
    pthread_t socketThread = startThread(socketMain);
    pthread_t distanceSensorThread = startThread(distanceSensorMain);
    pthread_t wheelSensorThread = startThread(wheelSensorMain);
    pthread_t speedThread = startThread(speedMain);
    pthread_t compassThread = startThread(compassMain);
    
    BCLLog("Threads Started",kLogMark);

    BCLLog("Program Waiting for Threads to Finish",kLogMark);
    
    joinThread(motorThread);
    joinThread(socketThread);
    //joinThread(distanceSensorThread);
    joinThread(wheelSensorThread);
    joinThread(speedThread);
    joinThread(compassThread);
    
    BCLLog("Program Ended",kLogMark);
    return 0;
}


void *motorMain() {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    
    do {
        if (!change) {
            usleep(10000);
            continue;
        }
        I2CData data;
        if(stop) {
            data = makeI2CDataFromSpeed(0, 0);
        }
        else {
            data = makeI2CDataFromSpeed(lSpeed, rSpeed);
        }
        sendI2CCommand(data, kMotorBoardID);
        free(data.command);
        change = 0;
    } while (true);
    
    return 0;
}

void *distanceSensorMain() {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    while(true) {
        usleep(1000000);
        int distance = getDistanceToObject();
        if(distance < 40){
            change = 1;
            stop = 1;
        }
        else {
            stop = 0;
        }

    }
}

void *wheelSensorMain() {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    wiringPiSetup();
    wiringPiISR(0, INT_EDGE_RISING, &wheelInterruptHandler);
    while(1){
        usleep(10000);
    }
    return  0;

}

void wheelInterruptHandler() {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    wheelCounter++;
}

void *speedMain() {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    while(true){
        int wheelCounter1 = wheelCounter;
        usleep(200000);
        int wheelCounter2 = wheelCounter;
        speed = (getDistanceTraveled(wheelCounter2-wheelCounter1)/0.2);
    }
}

void *compassMain() {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    while(true){
        bearing = getCompassValue();
        usleep(100000);
    }
}

void *socketMain() {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    socketListen(openSocket(port?port:5001, 0));
    return 0;
}

void socketListen(BCLSocket sockfd) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    while (true) {
        usleep(10000);
        void *obj = parseObject(sockfd);
        if (obj == NULL) {
            BCLLog("Emtpy Object",kLogWarning);
            break;
        }
        
        int type = ((struct BCLMessageObjDiscover*)obj)->messageType;
        
        if (type == kBCLMessageType_Unknown) {
            //
        }
        else if (type == kBCLMessageType_Request_CP) {
            //doBackGroundTaskWithCallback(answerRequest(sockfd,kBCLMessageType_Answer_CP));
            answerRequest(sockfd,kBCLMessageType_Answer_CP);
        }
        else if (type == kBCLMessageType_Request_SP) {
            //doBackGroundTaskWithCallback(answerRequest(sockfd,kBCLMessageType_Answer_SP));
            answerRequest(sockfd,kBCLMessageType_Answer_SP);

        }
        else if (type == kBCLMessageType_Request_DT) {
            //doBackGroundTaskWithCallback(answerRequest(sockfd,kBCLMessageType_Answer_DT));
            answerRequest(sockfd,kBCLMessageType_Answer_DT);
        }
        else if (type == kBCLMessageType_Answer_CP) {
            
        }
        else if (type == kBCLMessageType_Answer_SP) {
            
        }
        else if (type == kBCLMessageType_Answer_DT) {
            
        }
        else if (type == kBCLMessageType_Instruction_DR) {
            BCLMessageObjInsDR *object = obj;
            lSpeed = object->leftSpeed;
            rSpeed = object->rightSpeed;
            change = 1;
        }
        else if (type == kBCLMessageType_Instruction_ST) {
            BCLLog("Setting new speed",kLogMark);
            lSpeed = 0;
            rSpeed = 0;
            change = 1;
        }

    free(obj);
    } while (true);
    
    // n = write(sockfd,"I got your message",18);
    // if (n < 0) BCLError("ERROR writing to socket");
}

void *answerRequest(BCLSocket sockfd,kBCLMessageType type) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    if (type == kBCLMessageType_Answer_CP) {
        BCLMessageObjAnsCP *obj = malloc(sizeof(BCLMessageObjAnsCP));
        obj->messageType = kBCLMessageType_Answer_CP;
        obj->degrees = bearing;
        char *message = BCLMessageObjectToString(obj);
        send(sockfd, message, kBCLMessageLengthAnswer_CP, 0);
    }
    
    else if (type == kBCLMessageType_Answer_SP) {
        BCLMessageObjAnsSP *obj = malloc(sizeof(BCLMessageObjAnsSP));
        obj->messageType = kBCLMessageType_Answer_SP;
        obj->speed = speed;
        char *message = BCLMessageObjectToString(obj);
        send(sockfd, message, kBCLMessageLengthAnswer_SP, 0);
    }
    
    else if (type == kBCLMessageType_Answer_DT) {
        BCLMessageObjAnsDT *obj = malloc(sizeof(BCLMessageObjAnsDT));
        obj->messageType = kBCLMessageType_Answer_DT;
        obj->direction = getDistanceTraveled(wheelCounter);
        obj->distance = 123;
        char *message = BCLMessageObjectToString(obj);
        send(sockfd, message, kBCLMessageLengthAnswer_DT, 0);
    }
    
    typedef struct  BCLMessageObjAnsLP {
        kBCLMessageType messageType;
        int fineAmount;
        char *plate;
        char *name;
        char *offence;
        char *date;
    }  BCLMessageObjAnsLP;
    
    return NULL;
}

int getAnswerDataObject(void *obj) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    int type = ((struct BCLMessageObjDiscover*)obj)->messageType;

    if (type == kBCLMessageType_Unknown) {

    }
    
    else if (type == kBCLMessageType_Answer_CP) {
        // get message to send
    }
    
    else if (type == kBCLMessageType_Answer_SP) {
        // get message to send
    }
    
    else if (type == kBCLMessageType_Answer_DT) {
        // get message to send
    }

    return 0;
}

