#include <avr/io.h>
#include <stdbool.h>
#include "Waterswitch_Controller.h"

/*
water switch is connected to PB2
*/
void waterswitch_init()
{
    //pullup resistors for the 4 buttons
    PORTB |= (1<<PB2);
}

bool water_switch_on()
{
    return (PINB & 0x04);
}
