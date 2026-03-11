#include<stdint.h>
#include<stdbool.h>
#include<lis3mdltr.h>


void main()
{

full_scale read_fs_value=0xff;
out_rate ODR_reading = 0xff;
out_rate ODR_writedata = 0xff;
uint8_t interrupt_status = 0xFF;
int X_axis_val = 0;
int Y_axis_val = 0;
int Z_axis_val = 0;
sensor_init_stub(); // initialize test registers

//WE will call the functions that are intended to be done

//Get the full-scale configuration
read_fs_value = lis3mdltr_get_full_scale();


//Get and set the output data rate
ODR_reading = lis3mdltr_get_out_datarate();

//Set the required output datarate
//Assume we want to write value of 3 which corresponds to 5Hz
ODR_writedata = out_5hz;

lis3mdltr_set_out_datarate(ODR_writedata);

//Enable or disable the interrupt pin
interrupt_status = lis3mdltr_get_interrupt();

//Read the output data of a specified axis
X_axis_val = lis3mdltr_get_X_axis();
Y_axis_val = lis3mdltr_get_Y_axis();
Z_axis_val = lis3mdltr_get_Z_axis();

}