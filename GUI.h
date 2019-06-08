#ifndef GUI_H
#define GUI_H

#include <stdint.h>
#include "LCD_DISCO_F429ZI.h"
#include "TS_DISCO_F429ZI.h"
#include "cnst.h"


class Gui{
    private:    
        LCD_DISCO_F429ZI* _lcd;
        uint8_t _text[30];
            
        void _draw_logo_ensea(uint16_t x0, uint16_t y0);
        void _draw_title(void);
        
    public: 
       Gui(LCD_DISCO_F429ZI *lcdp);
       int display_ts_state(uint8_t ts_init);
       void display_cycle(uint8_t cycle);
       void display_current(float curr, float curr_p);
       void display_x_y(uint16_t xs, uint16_t ys);
       void display_state(STATES state);
};

class GuiButton {
    private:    
        int _x, _y, _w, _h;
        LCD_DISCO_F429ZI* _lcd;
        
    public: 
        int state;
        GuiButton(LCD_DISCO_F429ZI *lcdp, int xp, int yp, int wp, int hp);
       
        void display();
       
        void isClicked(int x_cur, int y_cur);
};

#endif

