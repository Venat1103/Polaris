# LSM 6DSO `IMU 1` | `SPI 2`
  - ## User Bank 0 Registers
    | Addr (Hex) | Register Name | Data |
    |-|-|-|
    01 | FUNC_CFG_ACCESS |
    0D | INT1_CTRL | `0b11`
    0F | WHO_AM_I
    10 | CTRL1_XL | `0b10000100`
    11 | CTRL2_G | `0b10001100`
    12 | CTRL3_C | `0b01000100`
    14 | CTRL5_C
    17 | CTRL8_XL | `0b0`
    19 | CTRL10_C | `0b100000`
    1E | STATUS_REG
    20 | OUT_TEMP_L | TEMP_DATA[7:0]
    21 | OUT_TEMP_H | TEMP_DATA[15:8]
    22 | OUTX_L_G | GYRO_DATA_X[7:0]
    23 | OUTX_H_G | GYRO_DATA_X[15:8]
    24 | OUTY_L_G | GYRO_DATA_Y[7:0]
    25 | OUTY_H_G | GYRO_DATA_Y[15:8]
    26 | OUTZ_L_G | GYRO_DATA_Z[7:0]
    27 | OUTZ_H_G | GYRO_DATA_Z[15:8]
    26 | OUTX_L_A | ACCEL_DATA_X[7:0]
    29 | OUTX_H_A | ACCEL_DATA_X[15:8]
    2A | OUTY_L_A | ACCEL_DATA_Y[7:0]
    2B | OUTY_H_A | ACCEL_DATA_Y[15:8]
    2C | OUTZ_L_A | ACCEL_DATA_Z[7:0]
    2D | OUTZ_H_A | ACCEL_DATA_Z[15:8]
    40 | TIMESTAMP0 | TIMESTAMP_DATA[31:24]
    41 | TIMESTAMP1 | TIMESTAMP_DATA[23:16]
    42 | TIMESTAMP2 | TIMESTAMP_DATA[15:8]
    43 | TIMESTAMP3 | TIMESTAMP_DATA[7:0]
    56 | TAP_CFG0 | `0b01000001`

  - ## Characteristics
    - ### Gyroscope
      - Gyroscope range: 2000 dps
      - Sensitivity for 2k dps: 70 mdps/LSB
      - Initial zero rate output tolerance: +- 1 dps
      - ODR: 1666 Hz
    - ### Accelerometer
      - Accelerometer range: 16 g
      - Sensitivity for 16 g: 0.488 mg/LSB
      - Initial zero rate output tolerance: +- 20 mg
      - ODR: 1666 Hz
    - ### Temperature
      - Sensitivity: 256 LSB/C
  - ## SPI
    - Pull CS to activate: LOW
    - Data delivered MSB first LSB last
    - Data transitioned on falling edge of SCLK
  - ## Self test at boot for later version
  - ## Interrupts
    - INT fire pull: HIGH
    - Use INT 1
    - INT fired when DATA READY, cleared when INT STATUS bit READ
  - ## Time stamp of reading stored in register, resolution of `25 us`
  - ## Power mode: 6-axis with independant ODR
  - ## Block data update
