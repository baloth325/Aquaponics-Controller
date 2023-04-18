#include <avr/io.h>
#include "LED_Controller.h"

void LED_init()
{
    DDRC |= 1 << DDC0;
    
}
void turn_on_LED()
{
    PORTC |= 1 << PC0;
}
void turn_off_LED()
{
    PORTC &= ~(1 << PC0);
}