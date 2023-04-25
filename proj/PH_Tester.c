#include "PH_Controller.h"
#include "LCD_Controller.h"
#include <util/delay.h>
#include <stdio.h>

int main(void)
{
PH_init();
lcd_init();
unsigned int ph;
char buffer [20];
unsigned int temp;
char temp_buffer [20];
while(1)
{
    lcd_clear();
    ph = PH_read();
    lcd_moveto(0,1);
    sprintf(buffer, "PH = %d", ph);
    lcd_stringout(buffer);
    char i;

    temp = Temp_read();
    lcd_moveto(1,1);
    sprintf(temp_buffer, "Temp = %d", temp);
    lcd_stringout(temp_buffer);

    for(i=0; i<4; i++)
    {
    _delay_ms(250);
    }

    
}
return 0;
}