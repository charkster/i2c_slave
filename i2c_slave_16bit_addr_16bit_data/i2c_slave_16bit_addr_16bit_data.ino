#include <Wire.h>
volatile uint8_t  address_upper;
volatile uint8_t  address_lower;
volatile uint16_t address;
volatile uint16_t memory_map [65536]; // array is initialized all low values
volatile uint8_t data_upper;
volatile uint8_t data_lower;

#define SLAVE_ID 0x3c

void setup()
{
  Wire1.setSDA(6); // this is for Xiao RP2040 and Xiao RP2350, must be Wire1 (channel 2)
  Wire1.setSCL(7);
  Wire1.begin(SLAVE_ID);         // join i2c bus with slave_id SLAVE_ID
  Wire1.onReceive(receiveEvent); // register write to slave
  Wire1.onRequest(requestEvent); // register read from slave
}

void loop()
{
  delay(100);
}

// function that executes when the master writes data to this slave
void receiveEvent(int bytes)
{
  address_upper = Wire1.read(); // read first byte to determine upper address byte
  address_lower = Wire1.read(); // read second byte to determine lower address byte
  address = (address_upper << 8) | address_lower;
  while (Wire1.available())
  {
    data_upper = Wire1.read();
    data_lower = Wire1.read();
    memory_map[address++] = (data_upper << 8) | data_lower;
  }
}

// function that executes when the master reads from this slave
void requestEvent()
{
  if (Wire1.available()) {       // not needed for rp2040 and rp2350, only for slow MCU
    address_upper = Wire1.read();
    address_lower = Wire1.read();
    address = (address_upper << 8) | address_lower;
  }
  for (int i = 0; i < 32; i++) // this is needed for multibyte reads, up to 32 bytes
  {
    data_upper = memory_map[address];
    data_lower = memory_map[address++];
    Wire1.write(data_upper);
    Wire1.write(data_lower);
  }
}

