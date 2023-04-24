#include <avr/io.h>
#include <util/delay.h>
#include "LCD_Controller.h"
SD_init()
{
    DDRD |= (1<<DDD2); PORTD |= (1<<DDD2); // PD2 is slave select for LCD
    UBRR0 = 0;
    DDRD |= (1<<DDD4); // DDR XCK = 1
    UCSR0C |= (1<<UMSEL00); UCSR0C |= (1<<UMSEL01);  //Sets to SPI master mode
    UCSR0C |= (1<<UCPOL0); UCSR0C |= (1<<UCPHA0); //SPI type 3
    UCSR0C &= ~(1<<UDORD0 ); // little endian
    UCSR0B |= (1 << TXEN0);  // Turn on transmitter
    UBRR0 = MYUBRR;

    // "put the SD card into SPI mode set MOSI and CS lines to logic value 1"

    PORTD |= (1<<DDD2);
    char i;
    for(i = 0; i < 11; i++)
    {
        while (!(UCSR0A & (1<<UDRE0)));
        UDR0 = 0xFF;
    }
    while (!(UCSR0A & (1<<UDRE0)));
    PORTD &= ~(1<<DDD2);
    UDR0 = 0x40;
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = 0x00;
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = 0x00;
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = 0x00;
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = 0x00;
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = 0x95;
    while (!(UCSR0A & (1<<UDRE0)));
    PORTD |= (1<<DDD2);







}