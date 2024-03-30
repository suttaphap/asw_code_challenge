#include "lis3mdl_driver.h"
#include <stdio.h>

int main() {
    uint8_t full_scale, odr;
    int16_t axis_data;
    status_t status;

    // Test: Get Full-scale Configuration
    printf(" Test: Get Full-scale Configuration\n");
    status = get_fullscale_config(&full_scale);
    if (status == STATUS_OK) {
        switch (full_scale) { // Print value based on Table 24 in the manual
        case 0:
            printf("Full-scale Configuration: ±4 gauss\n");
            break;
        case 1:
            printf("Full-scale Configuration: ±8 gauss\n");
            break;
        case 2:
            printf("Full-scale Configuration: ±12 gauss\n");
            break;
        case 3:
            printf("Full-scale Configuration: ±16 gauss\n");
            break;
        default:
            printf("Full-scale Configuration: Unknown (value = %u)\n", full_scale);
            break;
        }
    }
    else {
        printf("Failed to read full-scale configuration\n");
    }

    // Test: Get Output Data Rate
    printf(" Test: Get Output Data Rate\n");
    status = get_output_data_rate(&odr);
    if (status == STATUS_OK) {
        printf("Output Data Rate: %u\n", odr);
    }
    else {
        printf("Failed to read output data rate\n");
    }

    // Test: Set Output Data Rate (to 10Hz as an example)
    printf(" Test: Set Output Data Rate\n");
    status = set_output_data_rate(4); // The value 4 corresponds to 10Hz as per the case mapping
    if (status == STATUS_OK) {
        printf("Output Data Rate set to 10Hz successfully\n");
    }
    else {
        printf("Failed to set output data rate to 10Hz\n");
    }

    // Test: Enable Interrupt Pin
    printf(" Test: Enable Interrupt Pin\n");
    status = set_interrupt_pin(INT_EN);
    if (status == STATUS_OK) {
        printf("Interrupt pin enabled\n");
    }
    else {
        printf("Failed to enable interrupt pin\n");
    }

    // Test: Disable Interrupt Pin
    printf(" Test: Disable Interrupt Pin\n");
    status = set_interrupt_pin(INT_DIS);
    if (status == STATUS_OK) {
        printf("Interrupt pin disabled\n");
    }
    else {
        printf("Failed to disable interrupt pin\n");
    }

    // Test: Read Axis Data (for all three axes)
    printf("  Test: Read Axis Data\n");
    char axes[] = { 'X', 'Y', 'Z' };
    for (int i = 0; i < 3; i++) {
        status = read_axis_data(axes[i], &axis_data);
        if (status == STATUS_OK) {
            printf("Axis %c Data: %d\n", axes[i], axis_data);
        }
        else {
            printf("Failed to read data for axis %c\n", axes[i]);
        }
    }

    return 0;
}
