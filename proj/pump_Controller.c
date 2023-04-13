#include <avr/io.h>

void pump_init()
{
    DDRB |= 1 << DDB1;
}
void turn_on_pump()
{
    PORTB |= 1 << PB1;
}
void turn_off_pump()
{
    PORTB &= ~(1 << PB1);
}