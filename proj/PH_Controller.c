
#include <avr/io.h>
#include "PH_Controller.h"
#include <util/delay.h>


void PH_init()
{
    //Set the ADC clock prescalar
    #ifndef CLOCK_SPEED
        #define CLOCK_SPEED 8000000
    #endif
    #ifndef ADC_CLOCK
    #define ADC_CLOCK CLOCK_SPEED/64
    #endif
    //set the clock Prescalar to 64
    ADCSRA |= (1<<ADPS2);
    ADCSRA |= (1<<ADPS1);
    //Configure Refs to 0b00
    ADMUX &= ~(1<<REFS1);
    ADMUX &= ~(1<<REFS0);
    //Set ADLAR to zero for 10 bit resolution
    ADMUX &= ~(1<<ADLAR);
}
 int PH_read()
{
    //set mux select to read ADC2
    ADMUX &= 0xF0;
    ADMUX |= (1<<MUX1);
    //ADC Enable
    ADCSRA |= (1<<ADEN);
    // _delay_ms(250);
    //Start Conversion
    ADCSRA |= (1<<ADSC);

    while(!(ADCSRA & (1<<ADSC)))
    {}

    int data;
    int ph;
    data = ADC;
    ph = data * 14 / 1500;
    // ADCSRA &= ~(1<<ADEN);
    // _delay_ms(250);
    return ph;

}
int Temp_read()
{
        //set mux select to read ADC3
    ADMUX &= 0xF0;
    ADMUX |= (1<<MUX0);
    ADMUX |= (1<<MUX1);
    //ADC Enable
    ADCSRA |= (1<<ADEN);
    // _delay_ms(250);
    //Start Conversion
    ADCSRA |= (1<<ADSC);

    while(!(ADCSRA & (1<<ADSC)))
    {}

    int data;
    int temp;
    data = ADC;
    temp = data / 7;
    // ADCSRA &= ~(1<<ADEN);
    // _delay_ms(250);
    return temp;
    // _delay_ms(250);
}