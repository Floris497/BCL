//
//  BCLParse.c
//  Basic Control Layer
//
//  Created by Floris Fredrikze on 13/11/14.
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



#include "BCLParse.h"

void *parseObject(BCLSocket sockfd,void *obj) {
    //BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    
    char *peek = malloc(4);
    bzero(peek, 4);
    recv(sockfd, peek, 3,MSG_PEEK);
    BCLMark(peek);
    int type = detectMessageType(peek);
    
    
    if (type == kBCLMessageType_Unknown) {
        free(obj);
        return NULL;
    }
    
    
#pragma section Requests
    
    else if (type == kBCLMessageType_Request_CP) {
        char *unused = malloc(4);
        recv(sockfd, unused, 3, 0);
        obj = realloc(obj,sizeof(BCLMessageObjReqCP));
        BCLMessageObjReqCP *object = obj;
        object->messageType = kBCLMessageType_Request_CP;
    }
    
    else if (type == kBCLMessageType_Request_SP) {
        char *unused = malloc(4);
        recv(sockfd, unused, 3, 0);
        obj = realloc(obj,sizeof(BCLMessageObjReqSP));
        BCLMessageObjReqSP *object = obj;
        object->messageType = kBCLMessageType_Request_SP;
    }
    
    else if (type == kBCLMessageType_Request_DT) {
        obj = realloc(obj,sizeof(BCLMessageObjReqDT));
        char *buff; buff = getSocketMesg(sockfd, kBCLMessageLengthRequest_DT, buff);
        BCLMessageObjReqDT *object = obj;
        object->messageType = kBCLMessageType_Request_DT;
        object->direction = atoi(substring(buff, 3, 4));
        free(buff);
    }

#pragma section Answers

    else if (type == kBCLMessageType_Answer_CP) {
        obj = realloc(obj,sizeof(BCLMessageObjAnsCP));
        char *buff; buff = getSocketMesg(sockfd, kBCLMessageLengthAnswer_CP, buff);
        BCLMessageObjAnsCP *object = obj;
        object->messageType = kBCLMessageType_Answer_CP;
        object->degrees = atoi(substring(buff, 3, 4));
        free(buff);
    }
    
    else if (type == kBCLMessageType_Answer_SP) {
        obj = realloc(obj,sizeof(BCLMessageObjAnsSP));
        char *buff; buff = getSocketMesg(sockfd, kBCLMessageLengthAnswer_SP, buff);
         BCLMessageObjAnsSP *object = obj;
        object->messageType = kBCLMessageType_Answer_SP;
        object->speed = atoi(substring(buff, 3, 4));
        free(buff);
    }
    
    else if (type == kBCLMessageType_Answer_DT) {
        obj = realloc(obj,sizeof(BCLMessageObjAnsDT));
        char *buff; buff = getSocketMesg(sockfd, kBCLMessageLengthAnswer_DT, buff);
        BCLMessageObjAnsDT *object = obj;
        object->messageType = kBCLMessageType_Request_CP;
        object->distance = atoi(substring(buff, 3, 4));
        object->direction = atoi(substring(buff, 7, 4));
        free(buff);
    }
    
#pragma section Instructions

    else if (type == kBCLMessageType_Instruction_DR) {
        obj = realloc(obj,sizeof(BCLMessageObjInsDR));
        char *buff; buff = getSocketMesg(sockfd, kBCLMessageLengthInstruction_DR, buff);
        BCLMessageObjInsDR *object = obj;
        object->messageType = kBCLMessageType_Instruction_DR;
        object->leftSpeed = atoi(substring(buff, 3, 5));
        object->rightSpeed = atoi(substring(buff, 8, 5));
        free(buff);
    }
    
    else if (type == kBCLMessageType_Instruction_ST) {
        char *unused = malloc(4);
        recv(sockfd, unused, 3, 0);
        obj = realloc(obj,sizeof(BCLMessageObjInsST));
        BCLMessageObjInsST *object = obj;
        object->messageType = kBCLMessageType_Instruction_ST;
    }
    
    
    return obj;
};

kBCLMessageType detectMessageType(char *peek) {
    
    int kind = kBCLMessageType_Unknown;
    
    if (strcmp(peek,"CPR") == 0) {
        kind = kBCLMessageType_Request_CP;
    } else if (strcmp(peek,"SPR") == 0) {
        kind = kBCLMessageType_Request_SP;
    } else if (strcmp(peek,"DTR") == 0) {
        kind = kBCLMessageType_Request_DT;
    } else if (strcmp(peek,"CPA") == 0) {
        kind = kBCLMessageType_Answer_CP;
    } else if (strcmp(peek,"SPA") == 0) {
        kind = kBCLMessageType_Answer_SP;
    } else if (strcmp(peek,"DTA") == 0) {
        kind = kBCLMessageType_Answer_DT;
    } else if (strcmp(peek,"DRI") == 0) {
        kind = kBCLMessageType_Instruction_DR;
    } else if (strcmp(peek,"STI") == 0) {
        kind = kBCLMessageType_Instruction_ST;
    }
    
    return kind;
}

void *getSocketMesg(BCLSocket sockfd, size_t size,char *buffer) {
    buffer = malloc(size + kNullCharLengt);
    bzero(buffer, size + kNullCharLengt);
    recv(sockfd, buffer, size, 0);
    return buffer;
}

