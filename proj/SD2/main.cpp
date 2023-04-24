#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>

#include "diskio.h"
#include "pff.h"
#include "pffconf.h"
#include "spi.h"
#include "sdcard.h"

#include "../LCD_Controller.h"





int main(void)
{
    SPI_init();
    FATFS SD;
    DDRC |= 1 << DDC0; PORTC |= 1 << PC0;
    uint8_t i;

    for(i=0; i<8; i++) _delay_ms(250);

    i = pf_mount(&SD);

    if (i != 0)
    {
        char buffer[20];
        sprintf(buffer, "mount code = %d", i);
        lcd_init();
        lcd_stringout(buffer);
        return 1;
    }
    i=0;
    i = pf_open("TEST.TXT");
    if (i != 0)
    {
        char buffer[20];
        sprintf(buffer, "PF open = %d", i);
        lcd_init();
        lcd_stringout(buffer);
        PORTC &= ~(1<<PC0);
        return 1;
    }

    i = pf_lseek(0);
    UINT bw;
    //FRESULT pf_write (const void* buff, UINT btw, UINT* bw);	/* Write data to the open file */
    const char buff[] = "Test Test test I hate SD";
    const void* point = buff;
    UINT btw = 25;
    i = pf_write(point , btw, &bw);
        if (i != 0)
    {
        lcd_init();
    lcd_stringout("Error with PF write");

        return 1;
    }
    	pf_write(0, 0, &bw);



while(1)
{}

return 0;
}