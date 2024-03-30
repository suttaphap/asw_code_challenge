#ifndef LIS3MDL_DRIVER_H
#define LIS3MDL_DRIVER_H

#include "i2c.h" // Make sure this includes the I2C interface definitions
#include <stdbool.h>

// Address declarations
#define LIS3MDL_ADDRESS 0x1E // I2C address for LIS3MDL //assume the SDO/SA1 pin is connected to ground,
#define CTRL_REG1 0x20 // Control register 1 address
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define INT_CFG_REG 0x30 // Interrupt configuration register address

// Addresses of axis data registers
#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B
#define OUT_Z_L 0x2C
#define OUT_Z_H 0x2D

//Interupt Macro
#define INT_EN 	1
#define INT_DIS 0

// Function declarations
status_t get_fullscale_config(uint8_t* full_scale);
status_t get_output_data_rate(uint8_t* odr);
status_t set_output_data_rate(uint8_t odr);
status_t set_interrupt_pin(bool enable);
status_t read_axis_data(char axis, int16_t* data);

#endif // LIS3MDL_DRIVER_H
