DEVICE     = atmega328p
CLOCK      = 7372800
PROGRAMMER = -c usbtiny -P usb
AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)
SD_TEST: 
	$(COMPILE) -o SD.elf ./main.c ./diskio.c ./pff.c ./sdcard.c ./spi.c  
	rm -f ./SD.hex
	avr-objcopy -j .text -j .data -O ihex ./SD.elf ./SD.hex
	avr-size --format=avr --mcu=$(DEVICE) ./SD.elf
	$(AVRDUDE) -U flash:w:./SD.hex:i