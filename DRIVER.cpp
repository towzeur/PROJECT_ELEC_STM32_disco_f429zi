#include "DRIVER.h"
#include "mbed.h"
 
Driver::Driver(DigitalOut enp, DigitalOut in1p, DigitalOut in2p, AnalogIn adcp):
    _en(enp), _in1(in1p), _in2(in2p), _adc(adcp){
   
    _i_ratio = 0.0f;
    i_percent = 0.0f;
    i_current = 0.0f;
    
    this->stop();
}

void Driver::stop(void){
    _en = 0;
    _in1 = 0;
    _in2 = 0;
    this->_read_adc_ratio();
}
 
void Driver::down(void){
    _en = 1;
    _in1 = 1;
    _in2 = 0;
    this->_read_adc_ratio();
}

void Driver::up(void){
    _en = 1;
    _in1 = 0;
    _in2 = 1;
    this->_read_adc_ratio();
}

void Driver::get_current(void){
    this->_read_adc_ratio();
    i_percent = (_i_ratio) * 100.0f;
    i_current = (_i_ratio) * 2.8f;
}

void Driver::_read_adc_ratio(void){
    _i_ratio =  _adc.read();
}
 
 
 
 
