#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>

#include "diskio.h"
#include "pff.h"
#include "pffconf.h"
#include "spi.h"
#include "sdcard.h"






int main(void)
{

    FATFS SD;
    pf_mount(&SD);
    pf_open("Test.txt");
    UINT bw;
    //FRESULT pf_write (const void* buff, UINT btw, UINT* bw);	/* Write data to the open file */
    const char buff[] = "Test Test test";
    const void* point = buff;
    UINT btw = 136;
    pf_write(point , btw, &bw);





while(1)
{}

return 0;
}