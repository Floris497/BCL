//
//  main.c
//  Basic Control Layer
//
//  Created by Floris Fredrikze on 01/10/14.
//  Copyright (c) 2014 MiniMind. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>

#include "BCL.h"
#include "LowLevel.h"

pthread_mutex_t I2CMutex = PTHREAD_MUTEX_INITIALIZER;


int main(int argc, const char * argv[]) {
    
    return 0;
}

#pragma mark - I2C Manager
I2CData I2CTask(I2CCommand command) {
    // Lock so I2C is not used twise at a time
    pthread_mutex_lock(&I2CMutex);
    
    // Set 7bit slave for communication with the right device
    gpioI2cSet7BitSlave(command.device);
    
    // Determine if data must be send or recieved
    if (command.mode == I2C_SEND_MODE) {
        // Send data to device
        gpioI2cWriteData(command.data.command,command.data.commandLength);
    }
    else if (command.mode == I2C_RECIEVE_MODE) {
        // Read from device
        gpioI2cReadData(&command.data.command,command.data.commandLength);
    }
    else {
        printf("ERROR: wrong mode specified");
    }
    // It is Now safe to unlock the function
    pthread_mutex_unlock(&I2CMutex);
    
    // Return I2CData
    return command.data;
}