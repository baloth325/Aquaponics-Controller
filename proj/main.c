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
#include "TDS_Controller.h"
#include "PH_Controller.h"

volatile uint32_t timer_count = 0;
volatile unsigned char state = 0;
// volatile bool print_Flag = false;
volatile bool interruptEnabled = true;
// volatile char TDS_buffer [20];


//#define CLOCK_PRESCALAR 0x00    //must be in hex 2,4,8,16,32,64,128,or 256 following page60 in Atmel Documentation: Comment line if no prescalar desired


#ifdef CLOCK_PRESCALAR
    #ifndef F_CPU
    #define F_CPU 7372800
    #endif
    #define CLOCK_SPEED(CLOCK_PRESCALAR) (int)F_CPU/CLOCK_PRESCALAR4
#else
    #ifndef F_CPU
    #define F_CPU 7372800
    #endif
    #define CLOCK_SPEED F_CPU
#endif

ISR(TIMER1_COMPA_vect) {
    // Increment the timer count
    timer_count++;
    // char buffer[20];
    char i;
    unsigned int tds;
    char TDS_buffer [20];
    unsigned int cycle = 5;
    if(state == 11)
    {
        if(button_pressed('u'))
        {
            cycle = 3;
        }else if(button_pressed('d'))
        {
            cycle = 5;
        }else if(button_pressed('g'))
        {
            cycle = 10;
        }
    }
    if(state == 9)
    {
        if(timer_count == cycle)
        {
            // lcd_clear();
            // lcd_moveto(1,6);
            // sprintf(buffer, "%d", state);
            // lcd_stringout(buffer);
            // tds = TDS_read();
            // lcd_moveto(0,5);
            // sprintf(TDS_buffer, "TDS = %d", tds);
            // lcd_stringout(TDS_buffer);
            turn_on_chem_filter();
            turn_on_heater();
            turn_on_pump();
            for(i = 0; i < 4; i++)
            {
                _delay_ms(250);
            }
            turn_off_chem_filter();
            turn_off_heater();
            turn_off_pump();
            lcd_clear();
            timer_count = 0;
        } 
        
        if(button_pressed('a'))  
        {
            // lcd_moveto(0,10);
            // lcd_stringout("^");
            interruptEnabled = false;
            state = 8;
        }
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
    TDS_init();
    PH_init();
    TCCR1B |= (1 << WGM12) | (1 << CS12);
    OCR1A = 31249; // Compare value for 1 hour with 8 MHz clock and 256 prescalers
    TIMSK1 |= (1 << OCIE1A); // Enable timer compare interrupt
    sei();
    return;
}
int main(void)
{
    bool pump_is_on = false;
    bool chem_filter_is_on = false;
    bool bio_filter_is_on = false;
    bool heater_is_on = false;
    bool print_Flag = false;
    bool button_debounce = false;
    setup();
    state = 8;
    unsigned int tds;
    char TDS_buffer [20];
    unsigned int ph;
    char PH_buffer [20];

 

    while (1) {
        switch(state){
            case 0: // "Current Sensor Reading"
                if(!print_Flag){
                    lcd_clear();
                    lcd_moveto(0,10);
                    lcd_stringout("^");
                    lcd_moveto(1,2);
                    lcd_stringout("Sensor Readings");
                    lcd_moveto(3,10);
                    lcd_stringout("v");
                    print_Flag = true;
                }
                if(button_pressed('g') && !button_debounce)
                {
                    print_Flag = false;
                    state = 10;
                    button_debounce = true;
                }
                break;
            case 1: //"Program Timing of the Pump"
                if(!print_Flag){
                    lcd_clear();
                    lcd_moveto(0,10);
                    lcd_stringout("^");
                    lcd_moveto(1,4);
                    lcd_stringout("Program Pump");
                    lcd_moveto(2,2);
                    lcd_stringout("& Sensor Timing");
                    lcd_moveto(3,10);
                    lcd_stringout("v");
                    print_Flag = true;
                }
                if(button_pressed('g') && !button_debounce)
                {
                    state = 11;
                    print_Flag = false;
                    button_debounce = true;
                }
                break;
            case 2: //"Turn ON/OFF Pump"
                if(pump_is_on){
                    if (!print_Flag)
                    {
                        lcd_clear();
                        lcd_moveto(0,10);
                        lcd_stringout("^");
                        lcd_moveto(1,2);
                        lcd_stringout("Turn OFF the Pump");
                        lcd_moveto(3,10);
                        lcd_stringout("v");
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
                        lcd_moveto(0,10);
                        lcd_stringout("^");
                        lcd_moveto(1,2);
                        lcd_stringout("Turn ON the Pump");
                        lcd_moveto(3,10);
                        lcd_stringout("v");
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
            case 3: //"Turn ON/OFF Chemical Filter"
                if(chem_filter_is_on){
                    if (!print_Flag)
                    {
                        lcd_clear();
                        lcd_moveto(0,10);
                        lcd_stringout("^");
                        lcd_moveto(1,6);
                        lcd_stringout("Turn OFF");
                        lcd_moveto(2,2);
                        lcd_stringout("Chemical Filter");
                        lcd_moveto(3,10);
                        lcd_stringout("v");
                        print_Flag = true;
                    }           
                    if(button_pressed('g') && !button_debounce)
                    {
                        turn_off_chem_filter();
                        //refresh timeout variable
                        chem_filter_is_on = false;
                        print_Flag = false;
                        button_debounce = true;
                    } 
                }
                else{
                    if (!print_Flag)
                    {
                        lcd_clear();
                        lcd_moveto(0,10);
                        lcd_stringout("^");
                        lcd_moveto(1,6);
                        lcd_stringout("Turn ON");
                        lcd_moveto(2,2);
                        lcd_stringout("Chemical Filter");
                        lcd_moveto(3,10);
                        lcd_stringout("v");
                        print_Flag = true;
                    }
                    if(button_pressed('g') && !button_debounce)
                    {
                        turn_on_chem_filter();
                        //refresh timeout variable
                        chem_filter_is_on = true;
                        print_Flag = false;
                        button_debounce = true;
                    } 
                }
                break;
            case 4: //"Turn ON/OFF BioFilter"
                if(bio_filter_is_on){
                    if (!print_Flag){
                        lcd_clear();
                        lcd_moveto(0,10);
                        lcd_stringout("^");
                        lcd_moveto(1,6);
                        lcd_stringout("Turn OFF");
                        lcd_moveto(2,5);
                        lcd_stringout("Bio Filter");
                        lcd_moveto(3,10);
                        lcd_stringout("v");
                        print_Flag = true;
                    }
                    if(button_pressed('g') && !button_debounce)
                    {
                        turn_off_bio_filter();
                        //refresh timeout variable
                        bio_filter_is_on = false;
                        print_Flag = false;
                        button_debounce = true;
                    } 
                }
                else{
                    if (!print_Flag)
                    {
                        lcd_clear();
                        lcd_moveto(0,10);
                        lcd_stringout("^");
                        lcd_moveto(1,6);
                        lcd_stringout("Turn ON");
                        lcd_moveto(2,5);
                        lcd_stringout("Bio Filter");
                        lcd_moveto(3,10);
                        lcd_stringout("v");
                        print_Flag = true;
                    }
                    if(button_pressed('g') && !button_debounce)
                    {
                        turn_on_bio_filter();
                        //refresh timeout variable
                        bio_filter_is_on = true;
                        print_Flag = false;
                        button_debounce = true;
                    } 
                }
                break;
            case 5: //"Turn ON/OFF Heater"
                if(heater_is_on){
                    if (!print_Flag){
                        lcd_clear();
                        lcd_moveto(0,10);
                        lcd_stringout("^");
                        lcd_moveto(1,3);
                        lcd_stringout("Turn OFF Heater");
                        lcd_moveto(3,10);
                        lcd_stringout("v");
                        print_Flag = true;
                    }
                    if(button_pressed('g') && !button_debounce)
                    {
                        turn_off_heater();
                        //refresh timeout variable
                        heater_is_on = false;
                        print_Flag = false;
                        button_debounce = true;
                    } 
                }
                else{
                    if (!print_Flag)
                    {
                        lcd_clear();
                        lcd_moveto(0,10);
                        lcd_stringout("^");
                        lcd_moveto(1,3);
                        lcd_stringout("Turn ON Heater");
                        lcd_moveto(3,10);
                        lcd_stringout("v");
                        print_Flag = true;
                    }
                    if(button_pressed('g') && !button_debounce)
                    {
                        turn_on_heater();
                        //refresh timeout variable
                        heater_is_on = true;
                        print_Flag = false;
                        button_debounce = true;
                    } 
                }
                break;
            case 6: //"Turn OFF everything"
                if (!print_Flag)
                    {
                        lcd_clear();
                        lcd_moveto(0,10);
                        lcd_stringout("^");
                        lcd_moveto(1,0);
                        lcd_stringout("Turn OFF everything");
                        lcd_moveto(3,10);
                        lcd_stringout("v");
                        print_Flag = true;
                    }
                    if(button_pressed('g') && !button_debounce)
                    {
                        turn_off_pump();
                        pump_is_on = false;
                        turn_off_chem_filter();
                        chem_filter_is_on = false;
                        turn_off_bio_filter();
                        bio_filter_is_on = false;
                        turn_off_heater();
                        heater_is_on = false;

                        print_Flag = false;
                        button_debounce = true;
                    }
                    break;
            case 7: // "Go into sleep mode"
                if (!print_Flag)
                    {
                        lcd_clear();
                        lcd_moveto(0,10);
                        lcd_stringout("^");
                        lcd_moveto(1,5);
                        lcd_stringout("Sleep Mode");
                        lcd_moveto(3,10);
                        lcd_stringout("v");
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
                lcd_clear();
                lcd_moveto(1,6);
                lcd_stringout("Welcome");
                lcd_moveto(2,4);
                lcd_stringout("To Aquaponics");
                char i;
                for(i = 0; i<8; i++)
                {
                    _delay_ms(250);
                }
                lcd_clear();
                // for(i = 0; i<4; i++)
                // {
                //     _delay_ms(250);
                // }
                state = 0;
                break;
            case 9:
                lcd_clear();
                // lcd_off();
                interruptEnabled = true;
                break;
            case 10:
                lcd_clear();
                tds = TDS_read();
                lcd_moveto(0,1);
                sprintf(TDS_buffer, "TDS = %d", tds);
                lcd_stringout(TDS_buffer);

                ph = PH_read();
                lcd_moveto(1,1);
                sprintf(PH_buffer, "PH = %d", ph);
                lcd_stringout(PH_buffer);

                ph = Temp_read();
                lcd_moveto(2,1);
                sprintf(PH_buffer, "Temp = %d celcius", ph);
                lcd_stringout(PH_buffer);
                _delay_ms(250);

                if(button_pressed('r'))
                {
                    state = 0;
                    print_Flag = false;
                }
                break;
            case 11:
                if(!print_Flag)
                {
                    lcd_clear();
                    lcd_moveto(0,0);
                    lcd_stringout("Press 'U' to 10mins");
                    lcd_moveto(1,0);
                    lcd_stringout("Press 'D' to hourly");
                    lcd_moveto(2,0);
                    lcd_stringout("Press 'G' to daily");
                    lcd_moveto(3,0);
                    lcd_stringout("Press 'R' to return");
                    print_Flag = true;
                }
                if(button_pressed('r') && !button_debounce)
                {
                    state = 1;
                    print_Flag = false;
                    button_debounce = true;
                }else if(button_pressed('u') && !button_debounce ||
                         button_pressed('d') && !button_debounce ||
                         button_pressed('g') && !button_debounce)
                {
                    interruptEnabled = true;
                }
                break;
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
                
            }
        }
        if(!button_pressed('a'))
        {

            button_debounce = false;
        }
    }

    return 0;   /* never reached */
}
