#include <avr/io.h>


typedef struct{
int pinNum;
bool state;
} pumpController;



int main(void)
{

    while (1) {

	PORTC |= 1 << PC0;      // Set PC0 to a 1
	PORTC &= ~(1 << PC0);   // Set PC0 to a 0

    }

    return 0;   /* never reached */
}

