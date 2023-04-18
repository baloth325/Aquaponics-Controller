/*************************************************************
*       at328-6.c - Demonstrate interface to a serial LCD display
*
*       This program will print a message on an LCD display
*       using a serial interface.  It is designed to work with a
*       Matrix Orbital LK204-25 using an RS-232 interface.
*
* Revision History
* Date     Author      Description
* 11/07/07 A. Weber    First Release
* 02/26/08 A. Weber    Code cleanups
* 03/03/08 A. Weber    More code cleanups
* 04/22/08 A. Weber    Added "one" variable to make warning go away
* 04/11/11 A. Weber    Adapted for ATmega168
* 11/18/13 A. Weber    Renamed for ATmega328P
*************************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include "LCD_Controller.h"
/*
  lcd_init - Initialize the LCD
*/
extern void lcd_init()
{

    sci_init();                 // Initialize the SCI port

    _delay_ms(250);             // Wait 500msec for the LCD to start up
    _delay_ms(250);
   /* sci_out(0xFE);              // Clear the screen
    sci_out(0x51);
    sci_out(0xFE);              // Change brightness
    sci_out(0x53);
    sci_out(0b0111); */
}

/*
  moveto - Move the cursor to the row and column given by the arguments.
  Row is 0 or 1, column is 0 - 15.
*/
extern void lcd_clear()
{
    sci_out(0xFE);              // Clear the screen
    sci_out(0x51);
}
extern void lcd_moveto(unsigned char row, unsigned char col)
{
    sci_out(0xfe);              // Set the cursor position
    sci_out(0x45);
    if(row == 0)
    {
      sci_out(0x00 + col);
    }
    else if(row == 1)
    {
      sci_out(0x40 + col);
    }
    else if(row == 2)
    {
      sci_out(0x14 + col);
    }
    else if(row == 3)
    {
      sci_out(0x54 + col);
    }
    else
    {
      sci_out(0x00);
    }
}


/*
  lcd_stringout - Print the contents of the character string "str"
  at the current cursor position.
*/
extern void lcd_stringout(char *str)
{
    sci_outs(str);              // Output the string
}

/* ----------------------------------------------------------------------- */

/*
  sci_init - Initialize the SCI port
*/
void sci_init(void) {
    //OSCCAL |= 0x73;
    DDRD |= (1<<DDD2); PORTD |= (1<<DDD2); // PD2 is slave select for LCD
    UBRR0 = 0;
    DDRD |= (1<<DDD4); // DDR XCK = 1
    UCSR0C |= (1<<UMSEL00); UCSR0C |= (1<<UMSEL01);  //Sets to SPI master mode
    UCSR0C |= (1<<UCPOL0); UCSR0C |= (1<<UCPHA0); //SPI type 3
    //UCSR0C |= (1<<UDORD0 ); // little endian
    //UCSR0C |= (1 << UCSZ00);  // Set for asynchronous operation, no parity, 
    //UCSR0C |= (1 << UCSZ01);                  // one stop bit, 8 data bits
    UCSR0B |= (1 << TXEN0);  // Turn on transmitter
    UBRR0 = MYUBRR;

    ///toggle SS once to synchronize the LCD

    PORTD &= ~(1<<DDD2);
    PORTD |= (1<<DDD2);
    //UBRR0 = MYUBRR;          // Set baud rate
    
}

/*
  sci_out - Output a byte to SCI port
*/
void sci_out(char ch)
{
    PORTD &= ~(1<<DDD2);
    UDR0 = ch;
    while ( !(UCSR0A & (1<<UDRE0))) {};
    PORTD |= (1<<DDD2);

}

/*
  sci_outs - Print the contents of the character string "s" out the SCI
  port. The string must be terminated by a zero byte.
*/
void sci_outs(char *s)
{

    char ch;
    while ((ch = *s++) != '\0')
        sci_out(ch);
    PORTD |= (1<<DDD2);

}

