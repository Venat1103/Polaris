# Polaris
Open source flight computer

## Modules
- ### STM32 F446 VE Tx `MICROCONTROLLER`
- ### ICM 42688 P `IMU 0` - SPI 1

    | Function | Description | GPIO | Pin Mode
    |-|-|-|-|
    SCK | Clock | PA 5 | AF 5
    MOSI | Master Out | PA 7 | AF 5
    MISO | Master In | PA 6 | AF 5
    NSS | Slave Select | PA 4 | AF 5
    INT | Interrupt | PA 3 | Input

- ### LSM 6DSO 3 `IMU 1` - SPI 2

    | Function | Description | GPIO | Pin Mode
    |-|-|-|-|
    SCK | Clock | PB 13 | AF 5
    MOSI | Master Out | PC 1 | AF 7
    MISO | Master In | PC 2 | AF 5
    INT | Interrupt | PB 12 | Input

- ### MS 5607 02 BA 03 `BARO 0` - I2C 1

    | Function | Description | GPIO | Pin Mode | Pin Type
    |-|-|-|-|-|
    SCL | Clock | PB 8 | AF 4 | Open Drain
    SDA | Data | PB 7 | AF 4 | Open Drain

- ### LPS 22 HHTR `BARO 1` - I2C 3

    | Function | Description | GPIO | Pin Mode | Pin Type
    |-|-|-|-|-|
    SCL | Clock | PA 8 | AF 4 | Open Drain
    SDA | Data | PC 9 | AF 4 | Open Drain
    INT | Interrupt | PA 9 | Input

- ### NEO 7M `GPS` - USART 4

    | Function | Description | GPIO | Pin Mode
    |-|-|-|-|
    TX | Transmit | PA 0 | AF 8
    RX | Receive | PA 1 | AF 8

- ### Ai LoRaWAN Ra-08 (H) `RF` - USART 5

    | Function | Description | GPIO | Pin Mode
    |-|-|-|-|
    TX | Transmit | PE 8 | AF 8
    RX | Receive | PE 7 | AF 8

- ### PC 817 `OPTOCOUPLER` (x6) + IRL Z44 N `MOSFET` (x6)

    | Function | GPIO | Pin Mode
    |-|-|-|
    Main 0 | PD 9 | Output
    Main 1 | PD 10 | Output
    Drogue 0 | PD 14 | Output
    Drogue 1 | PD 15 | Output
    Fire 0 | PC 6 | Output
    Fire 1 | PC 7 | Output

- ### 32.768 kHz Crystal `RTC` - RCC OSC 32

    | Function | Description | GPIO |
    |-|-|-|
    RCC OSC IN | Oscillator In | PH 0
    RCC OSC OUT | Oscillator Out | PH 1

- ### Servos `ACTUATION`

    | Function | Description | GPIO | Pin Mode
    |-|-|-|-|
    Servo S0 | TIM12 CH1 | PB 14 | AF 9
    Servo S1 | TIM12 CH2 | PB 15 | AF 9
    Servo S2 | TIM1 CH1 | PE 9 | AF 1
    Servo S3 | TIM1 CH2 | PE 11 | AF 1
    Servo S4 | TIM1 CH3 | PE 13 | AF 1
    Servo S5 | TIM1 CH4 | PE 14 | AF 1

- ### Pyro Continuity Demultiplexer `DEMUX` CD 4051 B

    | Function | Description | GPIO | Pin Mode | Pin Type
    |-|-|-|-|-|
    MUX ENABLE | Multiplexer Enable | PC 0 | Output | Open Drain
    MUX A | Address Bit A | PC 13 | Output
    MUX B | Address Bit B | PC 14 | Output
    MUX C | Address Bit C | PC 15 | Output
    PYRO SENSE | Continuity ADC | PA 2 | Analog

- ### Micro SD `DATA`

    | Function | Description | GPIO | Pin Mode
    |-|-|-|-|
    SD CD | Card Detect | PD 1 | Input
    SD CLK | Clock | PB 2 | AF 12
    SD CMD | CMD | PD 2 | AF 12
    SD DAT 0 | Data Line 0 | PC 8 | AF 12
    SD DAT 1 | Data Line 1 | PB 0 | AF 12
    SD DAT 2 | Data Line 2 | PB 1 | AF 12
    SD DAT 3 | Data Line 3 | PC 11 | AF 12

- ### Flash `STORAGE`

    | Function | Description | GPIO | Pin Mode
    |-|-|-|-|
    Flash CLK | QuadSPI CLK | PD 3 | AF 9
    Flash CS | QuadSPI BK1 NCS | PB 6 | AF 10
    Flash IO0 | QuadSPI BK1 IO0 | PD 11 | AF 9
    Flash IO2 | QuadSPI BK1 IO2 | PE 2 | AF 9
    Flash IO1 | QuadSPI BK1 IO1 | PD 12 | AF 9
    Flash IO3 | QuadSPI BK1 IO3 | PD 13 | AF 9

- ### SWD `DEBUG`

    | Function | Description | GPIO | Pin Mode
    |-|-|-|-|
    SYS SW DIO | SYS JTMS SWDIO | PA 13 | AF 0
    SYS SW CLK | SYS JTCK SWCLK | PA 14 | AF 0

- ### USB `USB OTG FS`

    | Function | Description | GPIO | Pin Mode |
    |-|-|-|-|
    D- | USB OTG FS DM | PA 11 | AF 10
    D+ | USB OTG FS DP | PA 12 | AF 10

- ### LEDs and Buzzer `STATUS`

    | Function | GPIO | Pin Mode |
    |-|-|-|
    Buzzer | PD 0 | Output
    LED 1 | PD 4 | Output
    LED 2 | PD 5 | Output
    LED 3 | PD 6 | Output
    LED 4 | PD 7 | Output
