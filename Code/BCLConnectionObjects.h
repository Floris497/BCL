//
//  BCLConnectionObjects.h
//  Basic Control Layer
//
//  Created by Floris Fredrikze on 15/11/14.
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



#ifndef __Basic_Control_Layer__BCLConnectionObjects__
#define __Basic_Control_Layer__BCLConnectionObjects__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <poll.h>
#include <arpa/inet.h>

#define kBCLMessageLengthVarType 3
#define kBCLMessageLengthVarDegrees 4
#define kBCLMessageLengthVarSpeed 5
#define kBCLMessageLengthVarDistance 4

#define kNullCharLengt 1

#define kBCLMessageLengthRequest_CP kBCLMessageLengthVarType
#define kBCLMessageLengthRequest_SP kBCLMessageLengthVarType
#define kBCLMessageLengthRequest_DT kBCLMessageLengthVarType+kBCLMessageLengthVarDegrees

#define kBCLMessageLengthAnswer_CP kBCLMessageLengthVarType+kBCLMessageLengthVarDegrees
#define kBCLMessageLengthAnswer_SP kBCLMessageLengthVarType+kBCLMessageLengthVarSpeed
#define kBCLMessageLengthAnswer_DT kBCLMessageLengthVarType+kBCLMessageLengthVarDistance+kBCLMessageLengthVarDegrees

#define kBCLMessageLengthInstruction_DR kBCLMessageLengthVarType+kBCLMessageLengthVarSpeed+kBCLMessageLengthVarSpeed
#define kBCLMessageLengthInstruction_ST kBCLMessageLengthVarType

typedef enum kBCLMessageType {
    kBCLMessageType_Unknown,
    kBCLMessageType_Request_CP,
    kBCLMessageType_Request_SP,
    kBCLMessageType_Request_DT,
    
    kBCLMessageType_Answer_CP,
    kBCLMessageType_Answer_SP,
    kBCLMessageType_Answer_DT,
    
    kBCLMessageType_Instruction_DR,
    kBCLMessageType_Instruction_ST
} kBCLMessageType;


typedef struct BCLMessageObjDiscover {
    kBCLMessageType messageType;
} BCLMessageObjDiscover;


#pragma mark - messageType: Requests
typedef struct  BCLMessageObjReqCP {
    kBCLMessageType messageType;
}  BCLMessageObjReqCP;

typedef struct  BCLMessageObjReqSP {
    kBCLMessageType messageType;
}  BCLMessageObjReqSP;

typedef struct  BCLMessageObjReqDT {
    kBCLMessageType messageType;
    int direction;
}  BCLMessageObjReqDT;


#pragma mark - messageType: Answers
typedef struct  BCLMessageObjAnsCP {
    kBCLMessageType messageType;
    int degrees;
}  BCLMessageObjAnsCP;

typedef struct  BCLMessageObjAnsSP {
    kBCLMessageType messageType;
    int speed;
}  BCLMessageObjAnsSP;

typedef struct  BCLMessageObjAnsDT {
    kBCLMessageType messageType;
    int distance;
    int direction;
}  BCLMessageObjAnsDT;


#pragma mark - messageType: Instructions
typedef struct  BCLMessageObjInsDR {
    kBCLMessageType messageType;
    int leftSpeed;
    int rightSpeed;
}  BCLMessageObjInsDR;

typedef struct  BCLMessageObjInsST {
    kBCLMessageType messageType;
}  BCLMessageObjInsST;

#endif /* defined(__Basic_Control_Layer__BCLConnectionObjects__) */
