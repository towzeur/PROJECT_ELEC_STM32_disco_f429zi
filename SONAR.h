#ifndef HCSR04_H
#define HCSR04_H

#include "mbed.h"

class Sonar {    
    public:
        float dist_cm;       //distance value in "cm"
        float dist_in;       //distance value in "in"
        
        /** Constructor, create HCSR04 instance */
        Sonar(DigitalOut t, DigitalIn e);
 
        /** get the travel time and Update the distance
          * centimeter : dist_cm
          * inch "cm"  : dist_in
          */
        void get_distance(void);

        
    private:
        float _dt;           // elapsed time value

        DigitalOut _t;      // Trigger ref
        DigitalIn  _e;      // Echo    ref
        Timer     _tm;      // Timer   ref
        
        /** get the travel time in "us" */
        void _get_dt(void);
        
        /** update the distance in centimeter "in */
        void _update_cm(void);
        
        /** update the distance in centimeter "in */
        void _update_in(void);
};

#endif