#include <avr/io.h>
#include <stdbool.h>
#include "Button_Controller.h"


/*
up button is pin 14 PB0
down button is pin 13 Pd7
green is pin 12 pd6
red is pin 11 pd5
*/

void buttons_init()
{
    //pullup resistors for the 4 buttons
    PORTB |= (1<<PB0);
    PORTD |= (1<<PD7);
    PORTD |= (1<<PD6);
    PORTD |= (1<<PD5);
}

bool button_pressed(unsigned char button)
{
    if(button == 'u')
    {
        return !(PINB & 0x01);
    }
    if(button == 'd')
    {
        return !(PIND & 0x80);
    }
    if(button == 'g')
    {
        return !(PIND & 0x40);
    }
    if(button == 'r')
    {
        return !(PIND & 0x20);
    }
    if(button == 'a')
    {
        return (!(PINB & 0x01) || !(PIND & 0x80) || !(PIND & 0x40) || !(PIND & 0x20));
    }

    return 0;
}
