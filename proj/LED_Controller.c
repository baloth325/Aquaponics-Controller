#include <avr/io.h>
#include "LED_Controller.h"

void LED_init()
{
    DDRC |= 1 << DDC0;
    DDRB |= 1 << PB7;
    
}
void turn_on_red_LED()
{
    PORTC |= 1 << PC0;
}
void turn_off_red_LED()
{
    PORTC &= ~(1 << PC0);
}

void turn_on_heater()
{
    PORTB |= 1 << PB7;
}
void turn_off_heater()
{
    PORTB &= ~(1 << PB7);
}