/*************************************************************
*       at328-0.c - Demonstrate simple I/O functions of ATmega328
*
*       Program loops turning PC0 on and off as fast as possible.
*
* The program should generate code in the loop consisting of
*   LOOP:   SBI  PORTC,0        (2 cycles)
*           CBI  PORTC,0        (2 cycles)
*           RJMP LOOP           (2 cycles)
*
* PC0 will be low for 4 / XTAL freq
* PC0 will be high for 2 / XTAL freq
* A 9.8304MHz clock gives a loop period of about 600 nanoseconds.
*
* Revision History
* Date     Author      Description
* 09/14/12 A. Weber    Initial Release
* 11/18/13 A. Weber    Renamed for ATmega328P
*************************************************************/

#include <avr/io.h>


//#define CLOCK_PRESCALAR 0x00    //must be in hex 2,4,8,16,32,64,128,or 256 following page60 in Atmel Documentation: Comment line if no prescalar desired


#ifdef CLOCK_PRESCALAR
#define CLOCK_SPEED(CLOCK_PRESCALAR) (int)7372800/CLOCK_PRESCALAR
#else
#define CLOCK_SPEED 7372800
#endif


void setup()
{

    #ifdef CLOCK_PRESCALAR  // auto assigns clock prescalar
    CLKPR = 0x80;
    CLKPR = CLOCK_PRESCALAR;
    #else
    #endif 

    DDRC |= 1 << DDC0;          // Set PORTC bit 0 for output LED
    DDRB |= 1 << DDB1;          // Set PORTB bit 0 for output PUMP
    PORTB |= 1 << PB1;          //Turn on PUMP
    return;
}
void sleep_cycles(int sleepCycles)
{




}


int main(void)
{
    setup();

    while (1) {

	PORTC |= 1 << PC0;      // Set PC0 to a 1
	PORTC &= ~(1 << PC0);   // Set PC0 to a 0

    }

    return 0;   /* never reached */
}
