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
#include "LCD_Controller.c"
#include "pump_Controller.c"
#include "LED_Controller.c"
#include <util/delay.h>

//#define CLOCK_PRESCALAR 0x00    //must be in hex 2,4,8,16,32,64,128,or 256 following page60 in Atmel Documentation: Comment line if no prescalar desired


#ifdef CLOCK_PRESCALAR
#define CLOCK_SPEED(CLOCK_PRESCALAR) (int)8000000/CLOCK_PRESCALAR
#else
#define CLOCK_SPEED 8000000
#endif


void setup()
{
    #ifdef CLOCK_PRESCALAR  // auto assigns clock prescalar
    CLKPR = 0x80;
    CLKPR = CLOCK_PRESCALAR;
    #else
    #endif 

    pump_init();
    lcd_init();
    LED_init();

    return;
}
int main(void)
{
    setup();
    unsigned char state = 1;
    while (1) {
        switch(state){
            case 0:  // Enter sleep state


            case 1: // "Welcome to Aquaponics Controller"
            lcd_moveto(2,0);
            lcd_stringout("Welcome to Aquapoinics")
            for(uint i = 0; i<12; i++)
            {
                _delay_ms(250);
            }
            lcd_clear();
            state = 2;
            case 2: // "Current Sensor Reading"
                lcd_moveto(0,6);
                lcd_stringout("^");
                lcd_moveto(1,0);
                lcd_stringout("Current Sensor Readings")
                lcd_moveto(2,4);
                lcd_stringout("(Press Green)")
                lcd_moveto(3,6);
                sci_out(0xDA);
                


                /*
                if (up_button pressed)
                {
                    refresh timeout variable
                    case = 8
                }
                if (down_button pressed)
                {
                    refresh timeout variable
                    case = 3
                }
                if (select button pressed)
                {
                    refresh timeout variable
                    case = 10
                }
                if (back button pressed)
                {
                    refresh timeout variable
                }
                if(timeout)
                {
                    case = 0
                }
                
                
                */
            case 3: //"Program Timing of the Pump"


            case 4: //"Program Sensor Timing"


            case 5: //"Turn ON/OFF Pump"


            case 6: //"Turn ON/OFF Chemical Filter"


            case 7: //"Turn ON/OFF BioFilter"


            case 8: //"Turn OFF everything"


            case 9: // "Go into sleep mode"


            case 10: //Print all sensor readings:



        }
    }

    return 0;   /* never reached */
}
