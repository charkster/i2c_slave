#include <Wire.h>
volatile uint8_t address;
volatile uint8_t memory_map [256]; // array is initialize all low values

#define SLAVE_ID 0x3C

void setup()
{
  Wire1.setSDA(6);
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
  address = Wire1.read(); // read first byte to determine address
  while (Wire1.available())
  {
    memory_map[address++] = Wire1.read();
  }
}

// function that executes when the master reads from this slave
void requestEvent()
{
  if (Wire1.available()) {
     address = Wire1.read(); // slower MCU need to get address here, faster ones already updated address in receiveEvent()
  }
  for (int i = 0; i < 32; i++) // this is needed for multibyte reads, up to 32 bytes
  {
    Wire1.write(memory_map[address++]);
  }
}
