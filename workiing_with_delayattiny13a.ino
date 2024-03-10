#include <TinyWire.h>
const uint8_t TinyWire::SCL = 4;
const uint8_t TinyWire::SDA = 3;
const uint32_t TinyWire::FREQ = 100000;

unsigned char frequencyH = 0;
unsigned char frequencyL = 0;
unsigned int frequencyB;

const float frequencies[] PROGMEM = {91.10, 91.90, 92.70, 93.50, 94.30, 98.30, 100.10, 102.80, 104.00, 104.80, 106.40, 107.10};

void setup() {
  Wire.begin();
}

void loop() {
  for (int i = 0; i < 11; i++) {
    setFrequency(pgm_read_float_near(&frequencies[i]));
    delay(10000);
  }
}

void setFrequency(float frequency) {
  frequencyB = 4 * (frequency * 1000000 + 225000) / 32768;
  frequencyH = frequencyB >> 8;
  frequencyL = frequencyB & 0xFF;
  
  Wire.beginTransmission(0x60); // Adjusted I2C address
  Wire.write(frequencyH);
  Wire.write(frequencyL);
  Wire.write(0xB0);
  Wire.write(0x10);
  Wire.write((byte)0x00);
  Wire.endTransmission();
};