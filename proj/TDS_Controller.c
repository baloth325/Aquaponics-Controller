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
    //
}
unsigned int TDS_read()
{
    //set mux select to read ADC1
    ADMUX |= (1<<MUX0);
    //ADC Enable
    ADCSRA |= (1<<ADEN);
    //Start Conversion
    ADCSRA |= (1<<ADSC);

    while(!(ADCSRA & (1<<ADSC)))
    {}

    unsigned int data;

    data = ((ADCH & 0x03) << 8) | ADCL;
    return data;


}