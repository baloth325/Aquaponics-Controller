
#include <avr/io.h>
#include "TDS_Controller.h"
#include <util/delay.h>


void TDS_init()
{
    //Set the ADC clock prescalar
    #ifndef CLOCK_SPEED
        #define CLOCK_SPEED 8000000
    #endif
    #define ADC_CLOCK CLOCK_SPEED/64
    //set the clock Prescalar to 64
    ADCSRA |= (1<<ADPS2);
    ADCSRA |= (1<<ADPS1);
    //Configure Refs to 0b00
    ADMUX &= ~(1<<REFS1);
    ADMUX &= ~(1<<REFS0);
    //Set ADLAR to zero for 10 bit resolution
    ADMUX &= ~(1<<ADLAR);



}
 int TDS_read()
{
    //set mux select to read ADC1
    ADMUX &= 0xF0;
    ADMUX |= (1<<MUX0);
    //ADC Enable
    ADCSRA |= (1<<ADEN);
    // _delay_ms(250);
    //Start Conversion
    ADCSRA |= (1<<ADSC);

    while(!(ADCSRA & (1<<ADSC)))
    {}

    int data;
    int value;
    data = ADC;
    value = data / 3;
    // _delay_ms(250);
    return value;
}