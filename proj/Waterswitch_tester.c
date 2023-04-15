#include <stdbool.h>
#include <util/delay.h>
#include "Waterswitch_Controller.h"
#include "LCD_Controller.h"


int main(void)
{
    lcd_init();

    while(1)
    {
        lcd_moveto(0,1);
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
        }
    }
    return 0;
}