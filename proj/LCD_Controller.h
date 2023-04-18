#ifndef _PRIMARY_HEADER_LCD
#define _PRIMARY_HEADER_LCD

void lcd_init(void);
void lcd_moveto(unsigned char, unsigned char);
void lcd_stringout(char *);
void lcd_clear();

void sci_init(void);
void sci_out(char);
void sci_outs(char *);

    #define SPI_FLAG 1

    #define MYUBRR 47
    #ifndef MYUBRR 
        #ifdef CLOCK_SPEED
            #define FOSC CLOCK_SPEED
        #else
            #define FOSC 8000000UL		// Clock frequency
        #endif
        #define BAUD 9600UL              // Baud rate used by the LCD
        #define MYUBRR FOSC/16/BAUD-1   // Value for UBRR0 register
    #endif
#endif
