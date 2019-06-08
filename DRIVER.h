#ifndef DRIVER_H
#define DRIVER_H

#include "mbed.h"

class Driver {    
    public:    
        float i_percent;
        float i_current;
        
        /** Constructor, create Driver instance 
          *
          * @param DigitalOut ENB  pin
          * @param DigitalOut INB1 pin
          * @param DigitalOut INB2 pin
          * @param AnalogIn   ADCB pin
          */
        Driver(DigitalOut enp, DigitalOut in1p, DigitalOut in2p, AnalogIn adcp);
        
        /**  stop the jack*/
        void stop(void);
        
        /**  push down the jack*/
        void down(void);
        
        /** pull up the jack */
        void up(void);
        
        /** read and update i_current */
        void get_current(void);
        
    private:
        DigitalOut _en;
        DigitalOut _in1;
        DigitalOut _in2;
        AnalogIn _adc;
        
        float _i_ratio;
        void _read_adc_ratio(void); 
};

#endif



