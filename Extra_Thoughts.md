# LIS3MDL Magnetometer Driver - RTOS Improvements

This document outlines proposed changes to the LIS3MDL magnetometer driver to make it suitable for use in an RTOS (Real-Time Operating System) environment, as well as general improvements to the I2C API.

## Changes for RTOS Environment

### Task Scheduling
- Enable non-blocking I2C operations to allow tasks to relinquish control while awaiting the completion of I2C transactions.

### Synchronization Primitives
- Use mutexes or semaphores to protect the I2C bus access if shared by several tasks, preventing race conditions and ensuring thread safety.

### Priority Management
- Assign appropriate priorities to tasks interacting with the I2C driver to preserve determinism in a real-time system, ensuring higher priority tasks are not blocked by lower priority ones.

## Improvements to the I2C API

### Error Handling
- Expand the `status_t` enum with more specific error codes beyond `STATUS_OK` and `STATUS_ERROR`, allowing for more accurate error handling by the caller.

### Return Actual Data Length
- Modify the `i2c_read` function to return the actual number of bytes read, which may be less than requested in case of an error or an early stop condition.

### Buffer Management
- Implement buffer bounds checking within the `i2c_read` and `i2c_write` functions to prevent buffer overflows and underflows.

### Asynchronous Operations
- Introduce asynchronous versions of the read/write functions, which can be beneficial for RTOS-based and non-blocking architectures.
