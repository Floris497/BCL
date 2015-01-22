//
//  BCLExecute.c
//  Basic Control Layer
//
//  Created by Floris Fredrikze on 15/11/14.
//  Copyright (c) 2014 MiniMind. All rights reserved.
//

#include "BCLExecute.h"

void* getNextObjectSocket(BCLSocket sockfd) {
    BCLMarkFunc(__PRETTY_FUNCTION__,__FUNCTION__);
    return parseObject(sockfd);
}