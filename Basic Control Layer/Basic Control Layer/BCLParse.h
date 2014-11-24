//
//  BCLParse.h
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



#ifndef __Basic_Control_Layer__BCLParse__
#define __Basic_Control_Layer__BCLParse__

#include <stdio.h>
#include "BCLObjects.h"
#include "BCLConnectionObjects.h"
#include "BCLFunctions.h"

void *parseObject(BCLSocket sockfd);

kBCLMessageType detectMessageType();
void *getSocketMesg(BCLSocket sockfd, size_t size);


#endif /* defined(__Basic_Control_Layer__BCLParse__) */

