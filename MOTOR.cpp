
#include "MOTOR.h"


Motor::Motor(DigitalOut m1, DigitalOut m2): R1(m1), R2(m2){
    stop();
}

void Motor::stop(void){
    R2.write(1);
    wait_ms(100);
    
    R1.write(1);
    wait_ms(100);
}

void Motor::left(void){
    R1.write(1);
    wait_ms(100);
    
    R2.write(0);
    wait_ms(100);
    
    R1.write(0);
    wait_ms(100);
}


void Motor::right(void){
    R1.write(1);
    wait_ms(100);
    
    R2.write(1);
    wait_ms(100);
    
    R1.write(0);
    wait_ms(100);
}