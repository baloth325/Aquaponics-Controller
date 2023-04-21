#include <stdbool.h>
#include <util/delay.h>
#include "SD_Controller.h"
#include "LCD_Controller.h"



int main(void)
{
	uint8_t res[5], buf[512], token;
	SPI_init();
	uint8_t code = SD_init();
	

	if (code != 0)
	{
		DDRC |= (1<< PC0); PORTC |= (1<< PC0);
	}
	else
	{
		DDRB |= (1 << PB7); PORTB |= (1<<PB7);
	}
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);

	writeFile("test.txt", "This is a test");



while(1)
{}

return 0;
}