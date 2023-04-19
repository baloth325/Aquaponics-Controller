#include <stdbool.h>
#include <util/delay.h>
#include "Waterswitch_Controller.h"
#include "LCD_Controller.h"
<<<<<<< HEAD
#include <stdio.h>
=======
>>>>>>> 0814bc8cb30e4a4435c47d0ddaaf5d2910edaf5e


int main(void)
{
    lcd_init();
<<<<<<< HEAD
     lcd_moveto(0,1);
     long int fcpu;
        fcpu = F_CPU;

        char buffer[20];

        sprintf(buffer, "F_CPU= %ld", fcpu);
        lcd_stringout(buffer);
        
    while(1)
    {


        /*
        if(water_switch_on())
        {

=======

    while(1)
    {
        lcd_moveto(0,1);
        if(water_switch_on())
        {
>>>>>>> 0814bc8cb30e4a4435c47d0ddaaf5d2910edaf5e
            _delay_ms(250);
            lcd_clear();
            lcd_stringout(" water switch on");
        }
        else
        {
            _delay_ms(250);
            lcd_clear();
            lcd_stringout(" water switch off");
<<<<<<< HEAD
        }*/
=======
        }
>>>>>>> 0814bc8cb30e4a4435c47d0ddaaf5d2910edaf5e
    }
    return 0;
}