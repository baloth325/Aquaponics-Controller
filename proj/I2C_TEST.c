#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define BAUD_RATE 9600UL

#define I2C_ADDR 0x50 // default I2C address

void i2c_init() {
  // set SCL frequency to 50kHz
  TWBR = 32; // TWBR = (F_CPU / (2 * SCL frequency)) - 8
}

void i2c_start() {
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));
}

void i2c_stop() {
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void i2c_send_byte(uint8_t byte) {
  TWDR = byte;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));
}

void lcd_write_command(uint8_t cmd) {
  i2c_start();
  i2c_send_byte(I2C_ADDR << 1);
  i2c_send_byte(0xFE); // control byte for command
  i2c_send_byte(cmd);
  i2c_stop();
  _delay_us(50); // wait for command to be executed
}

void lcd_write_data(uint8_t data) {
  i2c_start();
  i2c_send_byte(I2C_ADDR << 1);
  //i2c_send_byte(0x40); // control byte for data
  i2c_send_byte(data);
  i2c_stop();
  _delay_us(50); // wait for data to be written
}

void lcd_init() {
  // initialize the LCD
  //lcd_write_command(0x38); // 8-bit data, 2-line display, 5x8 font
  lcd_write_command(0x41); // display on, cursor off, blink off
  lcd_write_command(0x51); // clear display
  lcd_write_command(0x46); // cursor moves right, no display shift
}

int main() {
  // initialize the I2C interface and the LCD
  i2c_init();
  lcd_init();
  
  // write "hello" to the LCD
  lcd_write_data('h');
  lcd_write_data('e');
  lcd_write_data('l');
  lcd_write_data('l');
  lcd_write_data('o');

  while (1) {
    // do nothing
  }

  return 0;
}
