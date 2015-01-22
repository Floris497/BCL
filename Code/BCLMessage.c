//
//  BCLMessage.c
//  Basic Control Layer
//
//  Created by Floris Fredrikze on 14/11/14.
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



#include "BCLMessage.h"

char* BCLMessageObjectToString(void *messageObject) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    int type = ((struct BCLMessageObjDiscover*)messageObject)->messageType;
    
#pragma mark Requests
    
    if (type == kBCLMessageType_Unknown) {
        BCLLog("Unknown Message Type",kLogError);
        return NULL;
    }
    else if (type == kBCLMessageType_Request_CP) {
        return getMessageTypeString(type);
    }
    else if (type == kBCLMessageType_Request_SP) {
        return getMessageTypeString(type);
    }
    else if (type == kBCLMessageType_Request_DT) {
        char *dest = malloc(kBCLMessageLengthRequest_DT + kNullCharLengt);
        BCLMessageObjReqDT *object = messageObject;
        char *messageTypeStr = getMessageTypeString(type);
        char *directionStr = malloc(kBCLMessageLengthVarDegrees + kNullCharLengt);
        intToStringWithSign(directionStr, kBCLMessageLengthVarDegrees, object->direction);
        sprintf(dest,"%s%s",messageTypeStr,directionStr);
        return dest;
    }
    
#pragma mark Answers
    
    else if (type == kBCLMessageType_Answer_CP) {
        char *dest = malloc(kBCLMessageLengthAnswer_CP + kNullCharLengt);
        char *messageTypeStr = getMessageTypeString(type);
        BCLMessageObjAnsCP *object = messageObject;
        char *degreesStr = malloc(kBCLMessageLengthVarDegrees + kNullCharLengt);
        intToStringWithSign(degreesStr, kBCLMessageLengthVarDegrees, object->degrees);
        sprintf(dest,"%s%s",messageTypeStr,degreesStr);
        return dest;
    }
    else if (type == kBCLMessageType_Answer_SP) {
        char *dest = malloc(kBCLMessageLengthAnswer_SP + kNullCharLengt);
        char *messageTypeStr = getMessageTypeString(type);
        BCLMessageObjAnsSP *object = messageObject;
        char *speedStr = malloc(kBCLMessageLengthVarSpeed + kNullCharLengt);
        intToStringWithSign(speedStr, kBCLMessageLengthVarSpeed, object->speed);
        sprintf(dest,"%s%s",messageTypeStr,speedStr);
        return dest;
    }
    else if (type == kBCLMessageType_Answer_DT) {
        char *dest = malloc(kBCLMessageLengthAnswer_DT + kNullCharLengt);
        char *messageTypeStr = getMessageTypeString(type);
        BCLMessageObjAnsDT *object = messageObject;
        char *directionStr = malloc(kBCLMessageLengthVarSpeed + kNullCharLengt);
        intToStringWithSign(directionStr, kBCLMessageLengthVarSpeed, object->direction);
        char *distanceStr = malloc(kBCLMessageLengthVarDistance + kNullCharLengt);
        intToStringWithSign(distanceStr, kBCLMessageLengthVarDistance, object->distance);
        sprintf(dest,"%s%s%s",messageTypeStr,directionStr,directionStr);
        return dest;
    }
    
#pragma mark Instructions
    
    else if (type == kBCLMessageType_Instruction_DR) {
        char *dest = malloc(kBCLMessageLengthInstruction_DR + kNullCharLengt);
        char *messageTypeStr = getMessageTypeString(type);
        BCLMessageObjInsDR *object = messageObject;
        char *lSpeedStr = malloc(kBCLMessageLengthVarSpeed + kNullCharLengt);
        intToStringWithSign(lSpeedStr, kBCLMessageLengthVarSpeed, object->leftSpeed);
        char *rSpeedStr = malloc(kBCLMessageLengthVarSpeed + kNullCharLengt);
        intToStringWithSign(rSpeedStr, kBCLMessageLengthVarSpeed, object->rightSpeed);
        sprintf(dest,"%s%s%s",messageTypeStr,lSpeedStr,rSpeedStr);
        return dest;
    }
    else if (type == kBCLMessageType_Instruction_ST) {
        return getMessageTypeString(type);
    }
    else {
        BCLLog("Wrong Message Type",kLogError);
        return NULL;
    }
    
    return NULL;
};

char* getMessageTypeString(kBCLMessageType type) {
    char *dest = malloc(kBCLMessageLengthVarType + kNullCharLengt);
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    if (type == kBCLMessageType_Unknown) {
        return NULL;
    } else if (type == kBCLMessageType_Request_CP) {
        dest = "CPR";
    } else if (type == kBCLMessageType_Request_SP) {
        dest = "SPR";
    } else if (type == kBCLMessageType_Request_DT) {
        dest = "DTR";
    } else if (type == kBCLMessageType_Answer_CP) {
        dest = "CPA";
    } else if (type == kBCLMessageType_Answer_SP) {
        dest = "SPA";
    } else if (type == kBCLMessageType_Answer_DT) {
        dest = "DTA";
    } else if (type == kBCLMessageType_Answer_DT) {
        dest = "LPA";
    } else if (type == kBCLMessageType_Instruction_DR) {
        dest = "DRI";
    } else if (type == kBCLMessageType_Instruction_ST) {
        dest = "STI";
    } else {
        return NULL;
    }
    
    return dest;
}

int intToStringWithSign(char* dest, size_t maxLength, int number) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    if (number >= 0) {
        sprintf(dest, "+%d",number);
    }
    else {
        sprintf(dest, "-%d",number);
    }
    dest = substring(dest, 0, maxLength);
    return 0;
}



