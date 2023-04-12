DEVICE     = atmega328p
CLOCK      = 9830400
PROGRAMMER = -c usbtiny -P usb
OBJECTS    = ./proj/main.c
FUSES      = -U hfuse:w:0xd9:m -U lfuse:w:0xe0:m
BIN_FOLDER = ./bin
PROJ_FOLDER = ./proj

# Fuse Low Byte = 0xe0   Fuse High Byte = 0xd9   Fuse Extended Byte = 0xff
# Bit 7: CKDIV8  = 1     Bit 7: RSTDISBL  = 1    Bit 7:
#     6: CKOUT   = 1         6: DWEN      = 1        6:
#     5: SUT1    = 1         5: SPIEN     = 0        5:
#     4: SUT0    = 0         4: WDTON     = 1        4:
#     3: CKSEL3  = 0         3: EESAVE    = 1        3:
#     2: CKSEL2  = 0         2: BOOTSIZ1  = 0        2: BODLEVEL2 = 1
#     1: CKSEL1  = 0         1: BOOTSIZ0  = 0        1: BODLEVEL1 = 1
#     0: CKSEL0  = 0         0: BOOTRST   = 1        0: BODLEVEL0 = 1
# External clock source, start-up time = 14 clks + 65ms
# Don't output clock on PORTB0, don't divide clock by 8,
# Boot reset vector disabled, boot flash size 2048 bytes,
# Preserve EEPROM disabled, watch-dog timer off
# Serial program downloading enabled, debug wire disabled,
# Reset enabled, brown-out detection disabled

# Tune the lines below only if you know what you are doing:

AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

# symbolic targets:
all:	main.hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

.c.s:
	$(COMPILE) -S $< -o $(BIN_FOLDER)/$@

flash:	all
	$(AVRDUDE) -U flash:w:$(BIN_FOLDER)/main.hex:i

fuse:
	$(AVRDUDE) $(FUSES)

# Xcode uses the Makefile targets "", "clean" and "install"
install: flash fuse

# if you use a bootloader, change the command below appropriately:
load: all
	bootloadHID $(BIN_FOLDER)/main.hex

clean:
	rm $(BIN_FOLDER)/*

# file targets:
main.elf: $(OBJECTS)
	$(COMPILE) -o $(BIN_FOLDER)/main.elf $(OBJECTS)

main.hex: main.elf
	rm -f $(BIN_FOLDER)/main.hex
	avr-objcopy -j .text -j .data -O ihex $(BIN_FOLDER)/main.elf $(BIN_FOLDER)/main.hex
	avr-size --format=avr --mcu=$(DEVICE) $(BIN_FOLDER)/main.elf
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.
I2C: ./proj/I2C_TEST.c
	$(COMPILE) -o $(BIN_FOLDER)/I2C.elf ./proj/I2C_TEST.c
	rm -f $(BIN_FOLDER)/I2C.hex
	avr-objcopy -j .text -j .data -O ihex $(BIN_FOLDER)/I2C.elf $(BIN_FOLDER)/I2C.hex
	avr-size --format=avr --mcu=$(DEVICE) $(BIN_FOLDER)/I2C.elf
	$(AVRDUDE) -U flash:w:$(BIN_FOLDER)/I2C.hex:i
# Targets for code debugging and analysis:
FLASH_I2C: 
	$(AVRDUDE) -U flash:w:$(BIN_FOLDER)/I2C.hex:i
RS232_TEST:
	$(COMPILE) -o $(BIN_FOLDER)/lcd.elf ./proj/LCD_Controller.c
WATER_SWITCH: RS232_TEST
	$(COMPILE) $(BIN_FOLDER)/lcd.elf ./proj/water_level_switch_test.c -o $(BIN_FOLDER)/water_switch.elf  
	rm -f $(BIN_FOLDER)/water_switch.hex
	avr-objcopy -j .text -j .data -O ihex $(BIN_FOLDER)/water_switch.elf $(BIN_FOLDER)/water_switch.hex
	avr-size --format=avr --mcu=$(DEVICE) $(BIN_FOLDER)/water_switch.elf
	$(AVRDUDE) -U flash:w:$(BIN_FOLDER)/water_switch.hex:i
disasm:	main.elf
	avr-objdump -d $(BIN_FOLDER)/main.elf

cpp:
	$(COMPILE) -E main.c
