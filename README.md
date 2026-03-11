# I²C Magnetometer Driver 

## Overview

This repository contains a simulation/stub implementation of I²C communication with the LIS3MDLTR 3-axis magnetometer. It is designed for testing and learning purposes without requiring actual hardware.

The implementation is based on the datasheet register map of the LIS3MDLTR and simulates register read/write behavior, including multi-byte axis readings and control registers.

The purpose is to provide a full understanding of how an I²C-based sensor driver works, including:

* Reading and writing to sensor registers
* Combining low/high bytes for 16-bit signed measurements
* Simulating control registers (ODR, full-scale, interrupt configuration)
* Testing driver logic in a **software-only environment**

---

## Features

* I²C Read/Write API Stubs: Functions `i2c_read()` and `i2c_write()` simulate I²C transactions.
* Register Simulation: `sensor_registers[256]` array mimics the magnetometer's internal registers.
* Axis Data Simulation: Registers `0x28`–`0x2D` contain arbitrary test values for X, Y, Z axes (low/high bytes).
* Control Registers: Registers like `0x20` (CTRL_REG1), `0x21` (CTRL_REG2), and `0x30` (INT_CFG) are initialized to realistic default values.
* Multi-byte Read/Write: Supports reading/writing multiple registers sequentially using loops and simulated auto-increment behavior.
* Signed 16-bit Axis Reading: Combines `*_L` and `*_H` bytes into a signed integer as the sensor would provide.

---

## Repository Structure

```
I2C_Magnetometer/
│
├── include/
│   └── i2c.h             # I2C API definitions (read/write prototypes)
│
├── src/
│   ├── i2c.c             # Stub I2C implementations (read/write functions)
│   ├── magnetometer.c    # High-level magnetometer driver functions
│   └── main.c            # Test program to demonstrate reading/writing registers
│
├── doc/
│   └── datasheet_notes.md  # Notes from LIS3MDLTR datasheet, register map
│
└── README.md             # Project overview and instructions
```

---

## How It Works

### 1Initialization

* `sensor_init_stub()` sets default values in the simulated registers:

```c
sensor_registers[0x20] = 0x70; // CTRL_REG1
sensor_registers[0x21] = 0x00; // CTRL_REG2 full-scale ±4G
sensor_registers[0x28] = 0x34; // X-axis low
sensor_registers[0x29] = 0x12; // X-axis high
sensor_registers[0x2A] = 0x56; // Y-axis low
sensor_registers[0x2B] = 0x78; // Y-axis high
sensor_registers[0x2C] = 0x9A; // Z-axis low
sensor_registers[0x2D] = 0xBC; // Z-axis high
sensor_registers[0x30] = 0x08; // INT_CFG
```

### Reading Data

* `i2c_read(bus_addr, reg_addr, length, buffer)` copies simulated register data to the buffer.
* Multi-byte reads use `register_address + i` to simulate auto-increment behavior.
* Example: Reading X-axis (16-bit signed):

```c
uint8_t buf[2];
i2c_read(0x1E, 0x28, 2, buf);
int16_t x = (int16_t)((buf[1] << 8) | buf[0]);  // Combine high & low bytes
```

### Writing Data

* `i2c_write(bus_addr, reg_addr, length, buffer)` copies buffer content into simulated registers.
* Example: Setting CTRL_REG2 full-scale:

```c
uint8_t fs_val = 0x20;  // ±8 gauss
i2c_write(0x1E, 0x21, 1, &fs_val);
```

---

## Usage / Testing

1. Compile the project (standard C compiler):

```bash
gcc src/*.c -I include -o magnetometer_test
```

2. Run the test program:

```bash
./magnetometer_test
```

3. Observe output for:

* X/Y/Z axis values
* Control register reads/writes
* Simulated I²C transactions

---

## Learning Outcomes : What I learnt from this project ? 

* Understanding I²C master-slave communication flow
* How to map datasheet registers to driver code
* Multi-byte read/write handling for 16-bit sensor data
* Abstracting hardware access for stub vs real sensor
* Preparing code structure suitable for RTOS or embedded environments
