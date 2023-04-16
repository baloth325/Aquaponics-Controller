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
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>
#include <avr/interrupt.h>


#include "LCD_Controller.h"
#include "pump_Controller.h"
#include "LED_Controller.h"
#include "Button_Controller.h"
#include "Waterswitch_Controller.h"

volatile uint32_t timer_count = 0;

//#define CLOCK_PRESCALAR 0x00    //must be in hex 2,4,8,16,32,64,128,or 256 following page60 in Atmel Documentation: Comment line if no prescalar desired


#ifdef CLOCK_PRESCALAR
#define CLOCK_SPEED(CLOCK_PRESCALAR) (int)8000000/CLOCK_PRESCALAR
#else
#define CLOCK_SPEED 8000000
#endif

ISR(TIMER1_COMPA_vect) {
    // Increment the timer count
    timer_count++;
    if(timer_count == 2)
    {
        timer_count = 0;
        turn_on_LED();
        _delay_ms(250);
        turn_off_LED();
    }
}

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
    buttons_init();
    TCCR1B |= (1 << WGM12) | (1 << CS12);
    OCR1A = 31249; // Compare value for 1 hour with 8 MHz clock and 256 prescaler
    TIMSK1 |= (1 << OCIE1A); // Enable timer compare interrupt
    return;
}
int main(void)
{
    bool pump_is_on = false;
    bool chem_filter_is_on = false;
    bool bio_filter_is_on = false;
    bool print_Flag = false;
    bool button_debounce = false;
    setup();
    unsigned char state = 8;

    

    while (1) {
        switch(state){
            case 0: // "Current Sensor Reading"
                if(!print_Flag){
                    lcd_clear();
                    lcd_moveto(0,6);
                    lcd_stringout("^");
                    lcd_moveto(1,0);
                    lcd_stringout("Sensor Readings");
                    lcd_moveto(2,4);
                    lcd_stringout("(Press Green)");
                    lcd_moveto(3,6);
                    sci_out(0xDA);
                    print_Flag = true;
                }
                break;
            case 1: //"Program Timing of the Pump"
                if(!print_Flag){
                    lcd_clear();
                    lcd_moveto(0,6);
                    lcd_stringout("^");
                    lcd_moveto(1,0);
                    lcd_stringout("Program Pump Timing");
                    lcd_moveto(2,4);
                    lcd_stringout("(Press Green)");
                    lcd_moveto(3,6);
                    sci_out(0xDA);
                    print_Flag = true;
                }
                break;
            case 2: //"Program Sensor Timing"
                if(!print_Flag){
                    lcd_clear();
                    lcd_moveto(0,6);
                    lcd_stringout("^");
                    lcd_moveto(1,0);
                    lcd_stringout("Program Sensor Timing");
                    lcd_moveto(2,4);
                    lcd_stringout("(Press Green)");
                    lcd_moveto(3,6);
                    sci_out(0xDA);
                    print_Flag = true;
                }
                break;
            case 3: //"Turn ON/OFF Pump"
                if(pump_is_on){
                    if (!print_Flag)
                    {
                        lcd_clear();
                        lcd_moveto(0,6);
                        lcd_stringout("^");
                        lcd_moveto(1,0);
                        lcd_stringout("Turn OFF the Pump");
                        lcd_moveto(2,4);
                        lcd_stringout("(Press Green)");
                        lcd_moveto(3,6);
                        sci_out(0xDA);
                        print_Flag = true;
                    }
                    
                    if(button_pressed('g') && !button_debounce)
                    {
                        turn_off_pump();
                        //refresh timeout variable
                        pump_is_on = false;
                        print_Flag = false;
                        button_debounce = true;
                    }                    
                }
                else{
                    if (!print_Flag)
                    {
                        lcd_clear();
                        lcd_moveto(0,6);
                        lcd_stringout("^");
                        lcd_moveto(1,0);
                        lcd_stringout("Turn ON the Pump");
                        lcd_moveto(2,4);
                        lcd_stringout("(Press Green)");
                        lcd_moveto(3,6);
                        sci_out(0xDA);
                        print_Flag = true;
                    }
                    if(button_pressed('g') && !button_debounce)
                    {
                        turn_on_pump();
                        //refresh timeout variable
                        pump_is_on = true;
                        print_Flag = false;
                        button_debounce = true;
                    }                    
                }
                break;
            case 4: //"Turn ON/OFF Chemical Filter"
                if(chem_filter_is_on){
                    if (!print_Flag)
                    {
                        lcd_clear();
                        lcd_moveto(0,6);
                        lcd_stringout("^");
                        lcd_moveto(1,0);
                        lcd_stringout("Turn OFF the Chem Filter");
                        lcd_moveto(2,4);
                        lcd_stringout("(Press Green)");
                        lcd_moveto(3,6);
                        sci_out(0xDA);
                        print_Flag = true;
                    }
                    /*
                    if(select button pressed)
                    {
                        turn on chem filter
                        refresh timeout variable
                        pump_is_on = false;
                        print_Flag = false;
                    }                    
                    */
                }
                else{
                    if (!print_Flag)
                    {
                        lcd_clear();
                        lcd_moveto(0,6);
                        lcd_stringout("^");
                        lcd_moveto(1,0);
                        lcd_stringout("Turn ON the Chem Filter");
                        lcd_moveto(2,4);
                        lcd_stringout("(Press Green)");
                        lcd_moveto(3,6);
                        sci_out(0xDA);
                        print_Flag = true;
                    }
                    /*
                    if(select button pressed)
                    {
                        turn_on_pump();
                        refresh timeout variable
                        pump_is_on = true;
                        print_Flag = false;
                    }                    
                    */
                }
                break;
            case 5: //"Turn ON/OFF BioFilter"
                if(bio_filter_is_on){
                    if (!print_Flag){
                        lcd_clear();
                        lcd_moveto(0,6);
                        lcd_stringout("^");
                        lcd_moveto(1,0);
                        lcd_stringout("Turn OFF the Bio Filter");
                        lcd_moveto(2,4);
                        lcd_stringout("(Press Green)");
                        lcd_moveto(3,6);
                        sci_out(0xDA);
                        print_Flag = true;
                    }
                    /*
                    if(select button pressed)
                    {
                        turn on chem filter
                        refresh timeout variable
                        pump_is_on = false;
                        print_Flag = false;
                    }                    
                    */
                }
                else{
                    if (!print_Flag)
                    {
                        lcd_clear();
                        lcd_moveto(0,6);
                        lcd_stringout("^");
                        lcd_moveto(1,0);
                        lcd_stringout("Turn ON the Bio Filter");
                        lcd_moveto(2,4);
                        lcd_stringout("(Press Green)");
                        lcd_moveto(3,6);
                        sci_out(0xDA);
                        print_Flag = true;
                    }
                    /*
                    if(select button pressed)
                    {
                        turn_on_pump();
                        refresh timeout variable
                        pum7p_is_on = true;
                        print_Flag = false;
                    }                    
                    */
                }
                break;
            case 6: //"Turn OFF everything"
                if (!print_Flag)
                    {
                        lcd_clear();
                        lcd_moveto(0,6);
                        lcd_stringout("^");
                        lcd_moveto(1,0);
                        lcd_stringout("Turn OFF everything");
                        lcd_moveto(2,4);
                        lcd_stringout("(Press Green)");
                        lcd_moveto(3,6);
                        sci_out(0xDA);
                        print_Flag = true;
                    }
            case 7: // "Go into sleep mode"
                if (!print_Flag)
                    {
                        lcd_clear();
                        lcd_moveto(0,6);
                        lcd_stringout("^");
                        lcd_moveto(1,0);
                        lcd_stringout("Sleep Mode");
                        lcd_moveto(2,4);
                        lcd_stringout("(Press Green)");
                        lcd_moveto(3,6);
                        sci_out(0xDA);
                        print_Flag = true;
                    }

                    if(button_pressed('g') && !button_debounce)
                    {
                        state = 9;
                        print_Flag = false;
                        button_debounce = true;
                    }
                    break;
            case 8: // "Welcome to Aquaponics Controller"
                lcd_moveto(1,6);
                lcd_stringout("Welcome");
                lcd_moveto(2,4);
                lcd_stringout("To Aquaponics");
                char i;
                for(i = 0; i<4; i++)
                {
                    _delay_ms(250);
                }
                lcd_clear();
                // for(i = 0; i<4; i++)
                // {
                //     _delay_ms(250);
                // }
                state = 0;
            case 9:
                lcd_clear();
                sei();
            /*case 9: //Print all sensor readings:
            if (!print_Flag)
                    {
                        lcd_clear();
                        lcd_moveto(0,0);
                        lcd_stringout("TDS Sensor: ");
                        lcd_moveto(1,0);
                        lcd_stringout("PH Sensor: ");
                        lcd_moveto(2,0);
                        lcd_stringout("Level Sensor: ");
                        lcd_moveto(3,0);
                        lcd_stringout("Suggestion:");
                        print_Flag = true;
                    } */
        }



        if(state < 8)
        {
            if(!button_debounce)
            {
                if(button_pressed('u'))
                {
                    if(state == 0)
                    {
                        state = 7;
                    }
                    else
                    {
                        state = state - 1;
                    }
                    button_debounce = true;
                    print_Flag = false;
                }
                else if (button_pressed('d'))
                {
                    if (state == 7)
                    {
                        state = 0;
                    }
                    else
                    {
                        state = state + 1;
                    }

                    button_debounce = true;
                    print_Flag = false;
                }
            }
            else
            {
                if(!button_pressed('a'))
                {
                    // lcd_clear();
                    // char buffer[20];
                    // sprintf(buffer, " %d", state);
                    // lcd_stringout(buffer);
                    // char i;
                    //  for(i = 0; i<4; i++)
                    //     {
                    //         _delay_ms(250);
                    //     }
                    button_debounce = false;
                }
            }
        }
    }

    return 0;   /* never reached */
}
