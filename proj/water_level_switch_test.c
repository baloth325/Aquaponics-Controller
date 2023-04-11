#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_VALUE F_CPU/16/BAUD-1

int main(void)
{
    // Set PB2 as input
    DDRB &= ~(1<<PB2);

    // Enable pull-up resistor on PB2
    PORTB |= (1<<PB2);

    // Set up serial communication
    UBRR0H = (uint8_t)(UBRR_VALUE>>8);
    UBRR0L = (uint8_t)(UBRR_VALUE);
    UCSR0B = (1<<TXEN0)|(1<<RXEN0);
    UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);

    while (1)
    {
        // Read the state of the water level switch
        if (bit_is_clear(PINB, PB2))
        {
            // Water level switch is closed
            printf("Water level switch closed\n");
        }
        else
        {
            // Water level switch is open
            printf("Water level switch open\n");
        }

        _delay_ms(500); // Wait for 500 milliseconds before reading again
    }

    return 0;
}
