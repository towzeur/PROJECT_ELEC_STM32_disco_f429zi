#ifndef MOTOR_H
#define MOTOR_H

#include "mbed.h"

class Motor {    
    public:
        DigitalOut R1;
        DigitalOut R2;
        
        /** Constructor, create HCSR04 instance */
        Motor(DigitalOut m1, DigitalOut m2);
        
        void stop(void);
        
        void left(void);
        
        void right(void);

};

#endif