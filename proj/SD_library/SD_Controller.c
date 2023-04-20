#define CMD0        0
#define CMD0_ARG    0x00000000
#define CMD0_CRC    0x94

SPI_init()
{
    DRD |= (1<<DDD3); PORTD |= (1<<DDD3); // PD3 is slave select for SD card
    UBRR0 = 0;
    DDRD |= (1<<DDD4); // DDR XCK = 1
    UCSR0C |= (1<<UMSEL00); UCSR0C |= (1<<UMSEL01);  //Sets to SPI master mode
    UCSR0C |= (1<<UCPOL0); UCSR0C |= (1<<UCPHA0); //SPI type 3
    UCSR0C &= ~(1<<UDORD0); // little endian
    UCSR0B |= (1 << TXEN0);  // Turn on transmitter
    UBRR0 = MYUBRR;
}
uint8_t SPI_transfer(uint8_t data)
{
    while(!( UCSRnA & (1<<UDREn)) );
    UDR0 = data;
    while ( !(UCSRnA & (1<<RXCn)) );
    return UDR0;
}
void SD_card_init()
{
    SD_Disable();
    _delay_ms(5);

    uint8_t i;
    for( i = 0; i < 10; i++)
    {
        SPI_transfer(0xFF);
    }
    SD_DISABLE();
    SPI_transfer(0xFF);

}
void SD_Disable()
{
    PORTD |= (1<<DDD3);
}
void SD_enable()
{
    PORTD &= ~(1<<DDD3);
}
SD_command(uint8_t cmd, uint32_t arg, uint8_t crc)
{
    SPI_transfer(cmd|=0x40);

    SPI_transfer((uint8_t)(arg >> 24));
    SPI_transfer((uint8_t)(arg >> 16));
    SPI_transfer((uint8_t)(arg >> 8));
    SPI_transfer((uint8_t)(arg));

    SPI_transfer(crc|0x01);
}
uint8_t SD_readRes1()
{
    uint8_t i = 0, res1;

    // keep polling until actual data received
    while((res1 = SPI_transfer(0xFF)) == 0xFF)
    {
        i++;

        // if no data received for 8 bytes, break
        if(i > 8) break;
    }

    return res1;
}
uint8_t SD_goIdleState()
{
    // assert chip select
    SPI_transfer(0xFF);
    CS_ENABLE();
    SPI_transfer(0xFF);

    // send CMD0
    SD_command(CMD0, CMD0_ARG, CMD0_CRC);

    // read response
    uint8_t res1 = SD_readRes1();

    // deassert chip select
    SPI_transfer(0xFF);
    CS_DISABLE();
    SPI_transfer(0xFF);

    return res1;
}
