#include "lis3mdltr.h"
#include "i2c.h"
#include <stdlib.h>


#define LIS3MDLTR_I2C_ADDR 0x1E //0001 1110b --> assumed SDO/SA1 pin is connected to Vdd


//List only those registers whose functionalities (Full Scale read, datarate, interrupt etc) we are going to use in this code

//Read ODR: Output Data Rate
#define CTRL_REG1 0x20

//Read the FS reading
#define CTRL_REG2 0x21

//Read the output of x axis
#define OUT_X_L 0x28 
#define OUT_X_H 0x29

//Read the output of y axis
#define OUT_Y_L 0x2A 
#define OUT_Y_H 0x2B

//Read the output of z axis
#define OUT_Z_L 0x2C 
#define OUT_Z_H 0x2D

//Read the interrupt en/ds
#define INT_CFG 0x30

// Full-scale
full_scale lis3mdltr_get_full_scale(void)
{
uint8_t *buffer = (uint8_t *)malloc(sizeof(uint8_t));
status_t returnType;
uint8_t temp;
//We are reading from CTRL_REG2 which is only 1 register, so length HAS TO be 1
returnType = i2c_read(LIS3MDLTR_I2C_ADDR,CTRL_REG2,1,buffer);

temp = *buffer;

// We need 5th and 6th bit to get the 

temp = (temp >> 5); //00000111
temp = (temp & 0x03);

return(temp);
}
//Get and set the output data rate
out_rate lis3mdltr_get_out_datarate(void)
{
uint8_t *buffer = (uint8_t *)malloc(sizeof(uint8_t));
status_t returnType;
uint8_t temp;
returnType = i2c_read(LIS3MDLTR_I2C_ADDR,CTRL_REG1,1,buffer);

temp = *buffer;

// We need 2-4th bit to get the 

temp = (temp >> 2); 
temp = (temp & 0x07);

return((out_rate)temp);
}

void lis3mdltr_set_out_datarate(out_rate DataRate)
{
uint8_t buffer = 0x00;
status_t returnType;

buffer = buffer | (int)(DataRate);
buffer = buffer << 2;
returnType = i2c_write(LIS3MDLTR_I2C_ADDR,CTRL_REG1,1,&buffer);


}



//Enable or disable the interrupt pin

uint8_t lis3mdltr_get_interrupt(void)
{
uint8_t *buffer = (uint8_t *)malloc(sizeof(uint8_t));
status_t returnType;
uint8_t temp;
returnType = i2c_read(LIS3MDLTR_I2C_ADDR,INT_CFG,1,buffer);

temp = *buffer;
temp=(temp & 0x01);
return ((uint8_t)temp);
}
//Read the output data of a specified axis


uint8_t lis3mdltr_get_X_axis(void)
{
uint8_t *buffer = (uint8_t *)malloc(2*sizeof(uint8_t));
status_t returnType;
uint8_t temp;
returnType = i2c_read(LIS3MDLTR_I2C_ADDR,OUT_X_L,2,buffer);

temp = *buffer;

return (temp);
}

uint8_t lis3mdltr_get_Y_axis(void)
{
uint8_t *buffer = (uint8_t *)malloc(2*sizeof(uint8_t));
status_t returnType;
uint8_t temp;
returnType = i2c_read(LIS3MDLTR_I2C_ADDR,OUT_Y_L,2,buffer);

temp = *buffer;

return (temp);
}


uint8_t lis3mdltr_get_Z_axis(void)
{
uint8_t *buffer = (uint8_t *)malloc(2*sizeof(uint8_t));
status_t returnType;
uint8_t temp;
returnType = i2c_read(LIS3MDLTR_I2C_ADDR,OUT_Z_L,2,buffer);

temp = *buffer;

return (temp);
}