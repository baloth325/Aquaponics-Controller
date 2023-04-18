#include <stdbool.h>
#include <util/delay.h>
#include "Waterswitch_Controller.h"
#include "LCD_Controller.h"
#include <stdio.h>


int main(void)
{
    lcd_init();
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

            _delay_ms(250);
            lcd_clear();
            lcd_stringout(" water switch on");
        }
        else
        {
            _delay_ms(250);
            lcd_clear();
            lcd_stringout(" water switch off");
        }*/
    }
    return 0;
}