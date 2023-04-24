#include "TDS_Controller.h"
#include "LCD_Controller.h"
#include <util/delay.h>
#include <stdio.h>

int main(void)
{
TDS_init();
lcd_init();
unsigned int tds;
char buffer [20];
while(1)
{
    tds = TDS_read();
    sprintf(buffer, "TDS = %d", tds);
    lcd_stringout(buffer);
    char i;
    for(i=0; i<8; i++)
    {
    _delay_ms(250);
    }
}
return 0;
}