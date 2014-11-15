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

int BCLMessageObjectToString(void *messageObject,char *dest) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    int type = ((struct BCLMessageObjDiscover*)messageObject)->messageType;
    
#pragma section Requests
    
    if (type == kBCLMessageType_Unknown) {
        BCLError("Unknown Message Type");
        return 1;
    }
    else if (type == kBCLMessageType_Request_CP) {
        dest = realloc(dest,kBCLMessageLengthRequest_CP + kNullCharLengt);
        getMessageTypeString(type, dest);
    }
    else if (type == kBCLMessageType_Request_SP) {
        dest = realloc(dest,kBCLMessageLengthRequest_SP + kNullCharLengt);
        getMessageTypeString(type, dest);
    }
    else if (type == kBCLMessageType_Request_DT) {
        dest = realloc(dest,kBCLMessageLengthRequest_DT + kNullCharLengt);
        char *messageTypeStr = realloc(dest,kBCLMessageLengthVarType + kNullCharLengt);
        getMessageTypeString(type, messageTypeStr);
        BCLMessageObjReqDT *object = messageObject;
        char *directionStr = realloc(dest,kBCLMessageLengthVarDegrees + kNullCharLengt);
        intToStringWithSign(directionStr, kBCLMessageLengthVarDegrees, object->direction);
        sprintf(dest,"%s%s",messageTypeStr,directionStr);
    }
    
#pragma section Answers
    
    else if (type == kBCLMessageType_Answer_CP) {
        dest = realloc(dest,kBCLMessageLengthAnswer_CP + kNullCharLengt);
        char *messageTypeStr = realloc(dest,kBCLMessageLengthVarType + kNullCharLengt);
        getMessageTypeString(type, messageTypeStr);
        BCLMessageObjAnsCP *object = messageObject;
        char *degreesStr = realloc(dest,kBCLMessageLengthVarDegrees + kNullCharLengt);
        intToStringWithSign(degreesStr, kBCLMessageLengthVarDegrees, object->degrees);
        sprintf(dest,"%s%s",messageTypeStr,degreesStr);
    }
    else if (type == kBCLMessageType_Answer_SP) {
        dest = realloc(dest,kBCLMessageLengthAnswer_SP + kNullCharLengt);
        char *messageTypeStr = realloc(dest,kBCLMessageLengthVarType + kNullCharLengt);
        getMessageTypeString(type, messageTypeStr);
        BCLMessageObjAnsSP *object = messageObject;
        char *speedStr = realloc(dest,kBCLMessageLengthVarSpeed + kNullCharLengt);
        intToStringWithSign(speedStr, kBCLMessageLengthVarSpeed, object->speed);
        sprintf(dest,"%s%s",messageTypeStr,speedStr);
    }
    else if (type == kBCLMessageType_Answer_DT) {
        dest = realloc(dest,kBCLMessageLengthAnswer_DT + kNullCharLengt);
        char *messageTypeStr = realloc(dest,kBCLMessageLengthVarType + kNullCharLengt);
        getMessageTypeString(type, messageTypeStr);
        BCLMessageObjAnsDT *object = messageObject;
        char *directionStr = realloc(dest,kBCLMessageLengthVarSpeed + kNullCharLengt);
        intToStringWithSign(directionStr, kBCLMessageLengthVarSpeed, object->direction);
        char *distanceStr = realloc(dest,kBCLMessageLengthVarDistance + kNullCharLengt);
        intToStringWithSign(distanceStr, kBCLMessageLengthVarDistance, object->distance);
        sprintf(dest,"%s%s%s",messageTypeStr,directionStr,directionStr);
    }
    
#pragma section Instructions
    
    else if (type == kBCLMessageType_Instruction_DR) {
        dest = realloc(dest,kBCLMessageLengthInstruction_DR + kNullCharLengt);
        char *messageTypeStr = realloc(dest,kBCLMessageLengthVarType + kNullCharLengt);
        getMessageTypeString(type, messageTypeStr);
        BCLMessageObjInsDR *object = messageObject;
        char *lSpeedStr = realloc(dest,kBCLMessageLengthVarSpeed + kNullCharLengt);
        intToStringWithSign(lSpeedStr, kBCLMessageLengthVarSpeed, object->leftSpeed);
        char *rSpeedStr = realloc(dest,kBCLMessageLengthVarSpeed + kNullCharLengt);
        intToStringWithSign(rSpeedStr, kBCLMessageLengthVarSpeed, object->rightSpeed);
        sprintf(dest,"%s%s%s",messageTypeStr,lSpeedStr,rSpeedStr);
    }
    else if (type == kBCLMessageType_Instruction_ST) {
        dest = realloc(dest,kBCLMessageLengthInstruction_ST + kNullCharLengt);
        getMessageTypeString(type, dest);
    }
    else {
        BCLError("Wrong Message Type");
        return 1;
    }
    
    return 0;
};

int getMessageTypeString(kBCLMessageType type, char *dest) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    if (type == kBCLMessageType_Unknown) {
        return 1;
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
    } else if (type == kBCLMessageType_Instruction_DR) {
        dest = "DRI";
    } else if (type == kBCLMessageType_Instruction_ST) {
        dest = "STI";
    } else {
        return 1;
    }
    
    return 0;
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
