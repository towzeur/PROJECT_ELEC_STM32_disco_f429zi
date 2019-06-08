/* Includes ------------------------------------------------------------------*/
#include "mbed.h"
#include "TS_DISCO_F429ZI.h"
#include "LCD_DISCO_F429ZI.h"
// custom
#include "cnst.h"
#include "GUI.h"
#include "DRIVER.h"
#include "SONAR.h"
#include "MOTOR.h"
#include "CAPTORS.h"


/* Pins binding and Variables ------------------------------------------------*/

//                                  LCD
LCD_DISCO_F429ZI LCD;
//                                  TOUCH SCREEN
TS_DISCO_F429ZI TS;
TS_StateTypeDef TS_State;
//                                  LED
DigitalOut Led1(LED1);
//                                  USER BUTTON
//DigitalIn BTN_USR(USER_BUTTON);
DigitalIn BTN_USR(PC_14);
//                                  SONAR
DigitalOut TRIGGER(PF_6);
DigitalIn     ECHO(PF_8); 
//                                  DRIVER
DigitalOut  ENB(PA_1); 
DigitalOut INB1(PC_5);
DigitalOut INB2(PA_7);
AnalogIn    ADCB(PA_5);
//                                  MOTOR
DigitalOut MR1(PC_3);
DigitalOut MR2(PC_1);
//                                  CAPTOR
DigitalIn L1(PA_0);
DigitalIn L2(PA_2);
DigitalIn R1(PF_7);
DigitalIn R2(PF_9);


/* ------------------------------------------------------------------------- */

int main()
{  
    /////////////////////////////////// INIT ///////////////////////////////////
    
    Gui gui(&LCD);                                         // init Gui
    GuiButton b0(&LCD, 110, 100, 65, 50);                  // init Gui_button 
    uint8_t ts = TS.Init(LCD.GetXSize(), LCD.GetYSize());  // init TS
    if (gui.display_ts_state(ts)) return 1;
    Sonar snr(TRIGGER, ECHO);                              // init Sonar
    Driver drv(ENB, INB1, INB2, ADCB);                     // init Driver
    Motor mtr(MR1, MR2);                                   // init Motor
    
    /////////////////////////////// EVENT LOOP /////////////////////////////////
    
    STATES state = UNKNOWN; 
    uint8_t cycle = 0;
    uint8_t l = 0;
    uint8_t root = 0;
    
    mtr.left();
    
    while(1){
        
        // INPUT : update entries
        TS.GetState(&TS_State);
        if (TS_State.TouchDetected ) b0.isClicked(TS_State.X, TS_State.Y);
        drv.get_current();
        //snr.get_distance();
        root = BTN_USR.read();

        // DISPLAY : user feedback
        b0.display();
        l = 1-l;
        Led1 = l;
        if (CNST_DEBUG){
            gui.display_cycle(cycle);
            gui.display_x_y(TS_State.X, TS_State.Y);
            gui.display_current(drv.i_current, drv.i_percent);  
            gui.display_state(state);
        }
        
        

        // OUTPUT : generate action
        switch (state){
    
            case UNKNOWN:
                if (root){
                    state=IDLE;
                    mtr.stop();
                }
                break;
                
            case IDLE:
                if (b0.state){
                    state=MOVE_RIGHT;
                    mtr.right();
                }
                break;
                
            case MOVE_LEFT:
                drv.down();

                if (root){
                    state=MOVE_RIGHT;
                    mtr.right();
                    cycle += 1;
                    if (cycle == CNST_NB_CYCLE+1){
                        state=END;
                        mtr.stop();
                    }
                }
                break;
                
            case MOVE_RIGHT:
                drv.down();

                if (root){
                    state=MOVE_LEFT;
                    mtr.left();
                }
                break;
                
            case END:
                while(1){};
                
            default:
                state=UNKNOWN;
        }
        
        // DEBOUNCE
        wait(CNST_REFRESH);
    }
}
