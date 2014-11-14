//
//  BCLParse.h
//  Basic Control Layer
//
//  Created by Floris Fredrikze on 13/11/14.
//  Copyright (c) 2014 MiniMind. All rights reserved.
//

#ifndef Basic_Control_Layer_BCLParse_h
#define Basic_Control_Layer_BCLParse_h

#include "LowLevel.h"

#define kParseLengtRequest_CP 3
#define kParseLengtRequest_SP 3
#define kParseLengtRequest_DT 6

#define kParseLengtAnswer_CP 6
#define kParseLengtAnswer_SP 6
#define kParseLengtAnswer_DT 10

#define kParseLengtInstruction_DR 12
#define kParseLengtInstruction_ST 3

typedef enum kParseReturnType {
    kParseReturnType_Request_CP,
    kParseReturnType_Request_SP,
    kParseReturnType_RequestDT,
    
    kParseReturnType_Answer_CP,
    kParseReturnType_Answer_SP,
    kParseReturnType_Answer_DT,
    
    kParseReturnType_Instruction_DR,
    kParseReturnType_Instruction_ST
} kParseReturnType;


typedef struct BCLParseTypeDiscover {
    kParseReturnType parseReturnType;
} BCLParseTypeDiscover;


#pragma mark - ParseType: Requests
typedef struct BCLParseObjReqCP {
    kParseReturnType parseReturnType;
} BCLParseObjReqCP;

typedef struct BCLParseObjReqSP {
    kParseReturnType parseReturnType;
} BCLParseObjReqSP;

typedef struct BCLParseObjReqDT {
    kParseReturnType parseReturnType;
} BCLParseObjReqDT;


#pragma mark - ParseType: Answers
typedef struct BCLParseObjAnsCP {
    kParseReturnType parseReturnType;
    int degrees;
} BCLParseObjAnsCP;

typedef struct BCLParseObjAnsSP {
    kParseReturnType parseReturnType;
    int speed;
} BCLParseObjAnsSP;

typedef struct BCLParseObjAnsDT {
    kParseReturnType parseReturnType;
    int distance;
    int direction;
} BCLParseObjAnsDT;


#pragma mark - ParseType: Instructions
typedef struct BCLParseObjInsDR {
    kParseReturnType parseReturnType;
    int leftSpeed;
    int rightSpeed;
} BCLParseObjInsDR;

typedef struct BCLParseObjInsST {
    kParseReturnType parseReturnType;
} BCLParseObjInsST;

void *ParseObject(BCLSocket *sockfd,void* obj);

#endif
