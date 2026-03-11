#include "i2c.h"

#include <stdint.h>
#include <stdio.h>

uint8_t sensor_registers[256];

// Optional: initialize some registers for testing for auto increment visualisation.
void sensor_init_stub(void)
{
    sensor_registers[0x28] = 0x34;  // X-axis low byte
    sensor_registers[0x29] = 0x12;  // X-axis high byte
    sensor_registers[0x2A] = 0x56;  // Y-axis low byte
    sensor_registers[0x2B] = 0x78;  // Y-axis high byte
    sensor_registers[0x2C] = 0x9A;  // Z-axis low byte
    sensor_registers[0x2D] = 0xBC;  // Z-axis high byte
    sensor_registers[0x20] = 0x70; // //Read the output data rate
    sensor_registers[0x21] = 0x00; ////Read the FS reading
    sensor_registers[0x30] = 0x08; // //Read the interrupt en/ds
}

status_t i2c_read(
    uint8_t bus_address,
    uint8_t register_address,
    uint16_t length,
    uint8_t *buffer)
{
    printf(
        "read [%d] bytes from bus [%d] for register [%d]\n",
        length,
        bus_address,
        register_address);

    /* Setting the output to some arbitrary value */
    # for (size_t i = 0; i < length; ++i) {
      	buffer[i] = i2c_read_byte(register_address + i);
    }

    return STATUS_OK;
}

status_t i2c_write(
    uint8_t bus_address,
    uint8_t register_address,
    uint16_t length,
    uint8_t *buffer)
{
    printf(
        "write [%d] bytes to bus [%d] for register [%d]\n\t",
        length,
        bus_address,
        register_address);

   for (size_t i = 0; i < length; ++i)
    {
        i2c_write_byte(register_address + i, buffer[i]);
    }

    return STATUS_OK;
}


#The function is kept as an abstraction layer.
#In the stub implementation it may simply return a value, 
#but in a real embedded system it would interact by waiting for acknowledgement 
#and for the register address with the I²C hardware to read a byte from the bus.

uint8_t i2c_read_byte(uint8_t reg_addr)
{
    // talk to hardware registers
    return sensor_registers[reg_addr];
}


void i2c_write_byte(uint8_t reg_addr, uint8_t data)
{
    sensor_registers[reg_addr] = data;  // copy data into simulated register

}
