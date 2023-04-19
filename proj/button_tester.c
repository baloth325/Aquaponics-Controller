#include <stdbool.h>
#include <util/delay.h>
#include "Button_Controller.h"
#include "LCD_Controller.h"





int main(void)
{
buttons_init();
lcd_init();
lcd_clear();
lcd_moveto(0,1);
lcd_stringout("Hello");
/*
while(1)
{
    lcd_moveto(0,1);
    if(button_pressed('u'))
    {
        lcd_clear();
        lcd_stringout("Up Button");
    }
    else if (button_pressed('d'))
    {
        lcd_clear();
        lcd_stringout("Down Button");
    }
    else if (button_pressed('g'))
    {
        lcd_clear();
        lcd_stringout("Green Button Pressed");
    }
    else if (button_pressed('r'))
    {
        lcd_clear();
        lcd_stringout("Red button pressed");
    }
    else
    {
        lcd_clear();
        lcd_stringout("No Button Pressed");
    }
}*/
return 0;
}