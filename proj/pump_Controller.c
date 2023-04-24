#include <avr/io.h>
#include "pump_Controller.h"

void pump_init()
{
    DDRB |= (1 << PB1);
}
void turn_on_pump()
{
    PORTB |= (1 << PB1);
}
void turn_off_pump()
{
    PORTB &= ~(1 << PB1);
}
