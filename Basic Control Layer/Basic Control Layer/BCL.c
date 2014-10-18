//
//  main.c
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

I2CData makeI2CDataFromSpeed(int16_t leftSpeed,int16_t rightSpeed,I2CData data){
    BCLWheel rWheel,lWheel;

    rWheel = getBCLWheelFromSpeed(rightSpeed, kMaxSpeedValue);
    lWheel = getBCLWheelFromSpeed(leftSpeed, kMaxSpeedValue);
    
    data.commandLength = 7;
    data.command[0] = kMotorDualSideCommand;
    data.command[1] = getHigh8bits(rWheel.speed);
    data.command[2] = getLow8bits(rWheel.speed);
    data.command[3] = getLow8bits(rWheel.direction);
    data.command[4] = getHigh8bits(lWheel.speed);
    data.command[5] = getLow8bits(lWheel.speed);
    data.command[6] = getLow8bits(lWheel.direction);
    
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




