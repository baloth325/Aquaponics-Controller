
#ifndef _PRIMARY_HEADER_SD
#define _PRIMARY_HEADER_SD


#define CMD0        0
#define CMD0_ARG    0x00000000
#define CMD0_CRC    0x94

#define CMD8        8
#define CMD8_ARG    0x0000001AA
#define CMD8_CRC    0x86 //(1000011 << 1)

#define CMD58       58
#define CMD58_ARG   0x00000000
#define CMD58_CRC   0x00

#define CMD55       55
#define CMD55_ARG   0x00000000
#define CMD55_CRC   0x00

#define ACMD41      41
#define ACMD41_ARG  0x40000000
#define ACMD41_CRC  0x00


void SPI_init();
uint8_t SPI_transfer(uint8_t data);
void SD_power_on_wait();
void SD_Disable();
void SD_enable();
void SD_command(uint8_t cmd, uint32_t arg, uint8_t crc);
uint8_t SD_readRes1();
uint8_t SD_goIdleState();
void SD_readRes7(uint8_t *res);
void SD_sendIfCond(uint8_t *res);
void SD_readOCR(uint8_t *res);
uint8_t SD_sendApp();
uint8_t SD_sendOpCond();
uint8_t SD_init();
uint8_t SD_readSingleBlock(uint32_t addr, uint8_t *buf, uint8_t *token);
uint8_t SD_writeSingleBlock(uint32_t addr, uint8_t *buf, uint8_t *token);



#endif