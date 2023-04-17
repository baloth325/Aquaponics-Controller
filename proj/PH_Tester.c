#include "PH_Controller.h"
#include "LCD_Controller.h"
#include <util/delay.h>
#include <stdio.h>

int main(void)
{
PH_init();
lcd_init();
unsigned int tds;
char buffer [20];
while(1)
{
    tds = PH_read();
    sprintf(buffer, "PH = %d", tds);
    lcd_stringout(buffer);
    char i;

    tds = Temp_read();
    sprintf(buffer, "Temp = %d", tds);
    lcd_stringout(buffer);

    for(i=0; i<8; i++)
    {
    _delay_ms(250);
    }

    
}
return 0;
}