#include "SONAR.h"
#include "mbed.h"
 
Sonar::Sonar(DigitalOut t, DigitalIn e) : _t(t), _e(e) {
    wait(0.1);
}

void Sonar::get_distance(void){
    this->_get_dt();
    this->_update_cm();
    this->_update_in();
}
 
void Sonar::_get_dt(void){     
    /* 
     * Generate the ultrasound by setting the Trig on a High State for 10 µs. 
     * That will send out an 8 cycle sonic burst traving at the speed sound and
     * they will be received back. The Echo pin will output the time in 
     * microseconds the sound wave traveled.
     */
    
    // Triger sequence
    _t=1;                      // set pulse
    wait_us(10);               // maintain 10us
    _t=0;                      // unset pulse
    
    // the wave come back
    while(!_e);                // wait the echo rising edge
    _tm.start();               // Start the timer
    while(_e);                 // wait the echo falling edge
    _tm.stop();                // Stop the timer
    
    // get the time and return
    _dt = _tm.read_us();     // Get the total time 
    _tm.reset();               // Reset the timer
}

void Sonar::_update_cm(void){
    dist_cm = _dt/58;
}
 
void Sonar::_update_in(void){
    dist_in = _dt/148;
}
 
