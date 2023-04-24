#include <avr/io.h>
#include "spi.h"

/*******************************************************************************
*   spi.c v1 - 11/02/2018
        Initial definitions
*   spi.c v2 - 11/07/2018
        Updated initialization functions
*******************************************************************************/

void SPI_init()
{
    DDRD |= (1<<DDD3); PORTD |= (1<<DDD3); // PD3 is slave select for SD card
    UBRR0 = 0;
    DDRD |= (1<<DDD4); // DDR XCK = 1
    UCSR0C |= (1<<UMSEL00); UCSR0C |= (1<<UMSEL01);  //Sets to SPI master mode
    UCSR0C &= ~(1<<UCPOL0); UCSR0C &= ~(1<<UCPHA0); //SPI type 0
    UCSR0C &= ~(1<<UDORD0); // little endian
    UCSR0B |= (1 << TXEN0);  // Turn on transmitter
    UCSR0B |= (1<< RXEN0);
    UBRR0 = 27;
}

uint8_t SPI_transfer(uint8_t data)
{
    while( !(UCSR0A & (1<<UDRE0)) );
    UDR0 = data;
    while ( !(UCSR0A & (1<<RXC0)) );
    return UDR0;
}
