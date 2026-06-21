# Polaris
Open source flight computer

## Modules
- STM32 F446 VE Tx `MICROCONTROLLER`
- ICM 42688 P `IMU 1` - SPI 3
- LSM 6DSO 3 `IMU 2` - SPI 2
- LPS 22 HHTR `BARO 2` - I2C 3
- MS 5607 - 02 BA 03 `BARO 1` - I2C 1
- NEO - M8N `GPS` - USART 2
- PC 817 `OPTOCOUPLER` (x6) + IRL Z44 N `MOSFET` (x6)
- 32.768 kHz Crystal `For RTC` - RCC OSC 32
