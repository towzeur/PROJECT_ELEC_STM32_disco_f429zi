#ifndef CNST_H
#define CNST_H

/* define     ----------------------------------------------------------------*/

enum STATES { 
    UNKNOWN, 
    IDLE,
    MOVE_LEFT, 
    MOVE_RIGHT,
    END
};

#define LCD_COLOR_ENSEA 0xFFC62A5B

/* Parameters ----------------------------------------------------------------*/

static int CNST_DEBUG = 1;        // display data IF DEBUG==1

static float CNST_REFRESH = 0.2;  // debounce time in second

static int CNST_NB_CYCLE = 2;



#endif