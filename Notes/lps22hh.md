# MS 5607 `BARO 1` | `I2C 3`
  - ## Registers
    | Addr (Hex) | Register Name | Data |
    |-|-|-|
    0B | INTERRUPT_CFG | `0b1100`
    0F | WHO_AM_I
    10 | CTRL_REG1 | `0b01010010`
    11 | CTRL_REG2 | `0b00010010`
    12 | CTRL_REG3 | `0b00000100`
    28 | PRESSURE_OUT_XL | POUT[7:0]
    29 | PRESSURE_OUT_L | POUT[15:8]
    2A | PRESSURE_OUT_H | POUT[23:16]
    2B | TEMP_OUT_L | TOUT[7:0]
    2C | TEMP_OUT_H | TOUT[15:8]
  - ## Characteristics
    - ### Range: 260 to 1260 hPa
    - ### ODR: 75 Hz (low noise mode)
    - ### Pressure Sensitivity: 4096 LSB/hPa
    - ### Temperature Sensitivity: 100 LSB/C
    - ### Resolution: 0.5 hPa
  - ## I2C
    - Address: `0b1011100`
    - Data delivered MSB first LSB last
    - Data transitioned on falling edge of SCLK
  - ## Interrupts
    - INT fire pull: HIGH
    - Use INT 1
    - INT fired when DATA READY, cleared when INT STATUS bit READ
  - ## Sequence
    1. Read pressure data stored in 3 registers
    2. Divide by 4096 LSB/hPa
    3. Read temperature data stored in 2 registers
    4. Divide by 100 LSB/C

    Visit datasheet page 9 for step-by-step calculations
