#include "lis3mdl_driver.h"
#include <stdbool.h>



status_t get_fullscale_config(uint8_t* full_scale)
{
    //Interact with CTRL_REG2 register to operate with full-scale configuration based on manaul. 
    uint8_t RegVal;
    status_t status = i2c_read(LIS3MDL_ADDRESS, CTRL_REG2, 1, &RegVal);
    if (status != STATUS_OK) 
    {
       return STATUS_ERROR;
    }

    *full_scale = (RegVal >> 5) & 0x03; // Extract FS[1:0] bits from CTRL_REG2
    return STATUS_OK;
}


status_t get_output_data_rate(uint8_t* ODR) 
{
    //Interact with CTRL_REG1 to operate with output data rate based on manaul.
    uint8_t tmp_odr, FAST_ODR, OM, DO;
    status_t status = i2c_read(LIS3MDL_ADDRESS, CTRL_REG1, 1, &tmp_odr);
    if (status != STATUS_OK) 
        return STATUS_ERROR;
    //reading FAST_ODR value
    FAST_ODR = (tmp_odr >> 1) & 0x1;

    if (FAST_ODR) 
    {
        //read OM value
        OM= (tmp_odr >> 5) & 0x3;
        //Set output data rate base on OM (Table 19,20 in manual)
        switch (OM) {
        case 0: *ODR = 1000; break; // Low-power mode: 1000 Hz
        case 1: *ODR = 560; break;  // Medium-performance mode: 560 Hz
        case 2: *ODR = 300; break;  // High-performance mode: 300 Hz
        case 3: *ODR = 155; break;  // Ultrahigh-performance mode: 155 Hz
        default: return STATUS_ERROR;
        }
    }
    else 
    {   //read DO bit
        DO = (tmp_odr >> 2) & 0x07; // Extract D0[2:0] bits from CTRL_REG2
        //Set output data rate base on DO (Table 21 in manual)
        switch (DO) {
        case 0: 
            *ODR = 0.625; 
            break;
        case 1: 
            *ODR = 1.25; 
            break;
        case 2: 
            *ODR = 2.5;
            break;
        case 3: 
            *ODR = 5; 
            break;
        case 4: 
            *ODR = 10; 
            break;
        case 5: 
            *ODR = 20; 
            break;
        case 6: 
            *ODR = 40; 
            break;
        case 7: 
            *ODR = 80;
            break;
        default: return STATUS_ERROR;
        }
    }

    return STATUS_OK;
}

status_t set_output_data_rate(uint8_t ODR) {
    uint8_t I2C_Write_Buffer;
    uint8_t OM;

    if (ODR < 8) { //when FAST_ODR = 0
        // Setting the DO[2:0] bits for standard data rate
        I2C_Write_Buffer = (ODR << 2) & 0x1C;

    }
    else if (ODR >= 8 && ODR <= 11) { //when FAST_ODR = 1
        // Setting the FAST_ODR Bit to ONE and setting OM[1:0] for high-speed data rate
        I2C_Write_Buffer = 0x02; // This sets the FAST_ODR bit

        switch (ODR) {
        case 8:
            OM = 0x3; // Corresponds to 155 Hz
            break;
        case 9:
            OM = 0x2; // Corresponds to 300 Hz
            break;
        case 10:
            OM = 0x1; // Corresponds to 560 Hz
            break;
        case 11:
            OM = 0x0; // Corresponds to 1000 Hz
            break;
        default:
            return STATUS_ERROR;
        }
        // Combining the FAST_ODR bit with the OM[1:0] bits
        I2C_Write_Buffer |= (OM << 5) & 0x60;
    }
    else {
        return STATUS_ERROR;
    }
    // Writing the new CTRL_REG1 configuration
    return i2c_write(LIS3MDL_ADDRESS, CTRL_REG1, 1, I2C_Write_Buffer);  
}

status_t set_interrupt_pin(bool enable) {
    uint8_t INT_cfg;
    status_t status;

    // Read the current value of the INT_CFG register
    status = i2c_read(LIS3MDL_ADDRESS, INT_CFG_REG, 1, &INT_cfg);
    if (status != STATUS_OK) {
        return status; // Return error if read operation failed
    }

    // Modify the IEN bit based on the enable parameter
    if (enable == INT_EN) {
        INT_cfg |= 0x01; // Set the IEN bit to enable interrupts
    }
    else if (enable == INT_DIS)
    {
        INT_cfg &= ~0x01; // Clear the IEN bit to disable interrupts
    }
    else
    {
        return STATUS_ERROR; // Return error if input isn't correct format
    }

    // Write the modified INT_CFG register value back to the device
    status = i2c_write(LIS3MDL_ADDRESS, INT_CFG_REG, 1, &INT_cfg);
    return status; // Return the status of the write operation

}

status_t read_axis_data(char axis, int16_t* Axis_data) {
    uint8_t addr_l, addr_h;
    uint8_t data_l, data_h;
    status_t status;

    // Determine the correct low and high data registers based on the axis
    switch (axis) {
    case 'X':
        addr_l = OUT_X_L;
        addr_h = OUT_X_H;
        break;
    case 'Y':
        addr_l = OUT_Y_L;
        addr_h = OUT_Y_H;
        break;
    case 'Z':
        addr_l = OUT_Z_L;
        addr_h = OUT_Z_H;
        break;
    default:
        return STATUS_ERROR; // Invalid axis
    }

    // Read the lower byte
    status = i2c_read(LIS3MDL_ADDRESS, addr_l, 1, &data_l);
    if (status != STATUS_OK) return status;

    // Read the higher byte
    status = i2c_read(LIS3MDL_ADDRESS, addr_h, 1, &data_h);
    if (status != STATUS_OK) return status;

    // Combine the high and low values to form a 16-bit result
    *Axis_data = (int16_t)(data_h << 8 | data_l);

    return STATUS_OK;

}
