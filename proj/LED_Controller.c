#include <avr/io.h>
#include "LED_Controller.h"

void LED_init()
{
    DDRC |= 1 << DDC0;
    DDRC |= 1 << DDC5;
    DDRB |= 1 << PB7;
    
}
void turn_on_chem_filter()
{
    PORTC |= 1 << PC0;
}
void turn_off_chem_filter()
{
    PORTC &= ~(1 << PC0);
}

void turn_on_bio_filter()
{
    PORTC |= 1 << PC5;
}
void turn_off_bio_filter()
{
    PORTC &= ~(1 << PC5);
}

void turn_on_heater()
{
    PORTB |= 1 << PB7;
}
void turn_off_heater()
{
    PORTB &= ~(1 << PB7);
}