# Files Overview

- `i2c.h`: Header file defining the structure and prototypes for I2C communication.
- `i2c.c`: Implementation of I2C communication. Currently contains stubs for `i2c_read` and `i2c_write`.
- `lis3mdl_driver.h`: Header file for the LIS3MDL magnetometer driver with function prototypes.
- `lis3mdl_driver.c`: Implementation of the LIS3MDL magnetometer driver with functionality for configuring the device and reading axis data.
- `main.c`: Main program used to test the functionality of the LIS3MDL driver.

## Testing the Driver

The `main` function in `main.c` tests the following functionalities:

- Reading the full-scale configuration of the magnetometer.
- Getting the current output data rate.
- Setting a new output data rate.
- Enabling the interrupt pin.
- Disabling the interrupt pin.
- Reading the magnetic field data from the X, Y, and Z axes.
