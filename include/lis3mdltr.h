#ifndef LIS3MDLTR_H
#define LIS3MDLTR_H

#include <stdint.h>

typedef enum
{
FS_4GS = 0,	
FS_8GS = 1,
FS_12GS = 2,
FS_16GS = 3,
invalid_fs=0xff
}full_scale;

// Full-scale
full_scale lis3mdltr_get_full_scale(void);

void lis3mdltr_set_full_scale(full_scale fs);


typedef enum
{
out_0p625hz = 0,
out_1p25hz = 1,
out_2p5hz = 2,
out_5hz = 3,
out_10hz = 4,
out_20hz = 5,
out_40hz = 6,
out_80hz = 7,
invalid_out=0xff
}out_rate;

out_rate lis3mdltr_get_out_datarate(void);

void lis3mdltr_set_out_datarate(out_rate ot);


uint8_t lis3mdltr_get_interrupt(void);

uint8_t lis3mdltr_get_X_axis(void);
uint8_t lis3mdltr_get_Y_axis(void);
uint8_t lis3mdltr_get_Z_axis(void);


#endif
