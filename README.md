# i2c_slave
Arduino implementation of I2C slave. Tested on SAMD21, RP2040 and RP2350.

Directories with pre-built uf2 files are available... just drag-n-drop if you have a Xiao RP2040, Xiao RP2350 or QT PY SAMD21 board. No need to install Arduino if you don't want to.

Why would you want a MCU board to become an I2C slave? If you are waiting for an IC and want to test the system before it arrives... or if you believe an IC is damaged and want to test your software, this is a good way to do that.


The Arduino Wire library is used. "Wire1" instance refers to I2C channel 1, and "Wire" instance refers to channel 0. For the Xiao RP2040 and RP2350 boards only channel 1 pins are available. For the QT PY SAMD21 board only channel 0 pins are available. The INO files are written for "Wire1", but you can easily change that to "Wire" for your board if needed.
