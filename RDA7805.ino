#define SDA_PIN 0  // Adjust these values based on your actual pin connections
#define SCL_PIN 1

void i2c_start() {
  PORTB |= (1 << SDA_PIN); // SDA high
  PORTB |= (1 << SCL_PIN); // SCL high
  _delay_us(4);
  PORTB &= ~(1 << SDA_PIN); // SDA low
  _delay_us(4);
  PORTB &= ~(1 << SCL_PIN); // SCL low
}

void i2c_stop() {
  PORTB &= ~(1 << SDA_PIN); // SDA low
  PORTB |= (1 << SCL_PIN); // SCL high
  _delay_us(4);
  PORTB |= (1 << SDA_PIN); // SDA high
  _delay_us(4);
}

void i2c_write_byte(uint8_t byte) {
  for (uint8_t i = 0; i < 8; i++) {
    if (byte & 0x80) {
      PORTB |= (1 << SDA_PIN); // SDA high
    } else {
      PORTB &= ~(1 << SDA_PIN); // SDA low
    }
    byte <<= 1;
    _delay_us(2);
    PORTB |= (1 << SCL_PIN); // SCL high
    _delay_us(4);
    PORTB &= ~(1 << SCL_PIN); // SCL low
    _delay_us(2);
  }
  // Receive ACK
  PORTB |= (1 << SDA_PIN); // SDA high (release SDA)
  _delay_us(2);
  PORTB |= (1 << SCL_PIN); // SCL high
  _delay_us(2);
  if (PINB & (1 << SDA_PIN)) {
    // Not ACK received
    // Handle the error or implement retries
  }
  PORTB &= ~(1 << SCL_PIN); // SCL low
  _delay_us(4);
}

void setup() {
  DDRB |= (1 << SDA_PIN) | (1 << SCL_PIN);  // Set SDA and SCL pins as output
  i2c_start();
  i2c_write_byte(0x20);  // Write address
  i2c_write_byte(0x24);  // Set frequency MSB (0x24)
  i2c_write_byte(0xE6);  // Set frequency LSB (0xE6)
  i2c_stop();
  _delay_ms(300);
}


void loop() {}
