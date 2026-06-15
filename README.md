# Polaris
Open source flight computer
##  High-Level Flight Computer Architecture
![Polestar System architecture](./images/Polaris.svg)

## 1. Power:
The whole system is powered by a single 2S Li-Po battery that can be charged via USB-C PD.
- Main Power Rail: 7.4-8.4V from battery or 9V from USB-C PD
- Battery charger IC: Texas Instruments BQ24005
- 5V regulator (switching): Texas Instruments LMR51430
- 3.3V regulator (linear): ON Semiconductor NCP1117-3.3
- 3.3V RF regulator (linear): Texas Instruments TPS7A2033
- USB-PD negotiation: WCH CH224K
## 2. Processing:
- Navigation and Guidance: ST Microelectronics STM32F412RGT6 (NAV)
- Telemetry: Raspberry Pi RP2040 (TLM)
## 3. Sensors:
All connected to NAV only
- IMUs:
	- Main IMU: TDK InvenSense ICM42688-P
	- High-G Accelerometer: ST Microelectronics LSM6DSO32
- Barometric Pressure Sensors:
	- TE Connectivity MS5607-02BA03
	- ST Microelectronics LPS22HHTR
- GNSS Module: u-blox GPS NEO-M8N

I used the LSM6DSO32 since dedicated high-G accelerometers were either unavailable or too expensive.\
I used two barometers for redundancy.\
I used the GPS NEO-M8N instead of the cheaper NEO-7M since it has reached EoL.
## 4. Communication and Logging:
TLM handles telemetry through:
- Wireless Radio: Ai-Thinker Ra-08H
- Logging: MicroSD Card slot 

The Ra-08H is a fairly cheap LoRa module based on the ASR6601 SoC
## 5. Active Control:
Active control is achieved through 4 servo lines controlled via PWM signals from NAV. \
The board supports both thrust vector control (through the first two servo lines) and fin control (through all four servo lines) \
The servos must be high-power and operate at up to 9V.
## 6. Others:
The board supports firing the motor and all parachutes using firing leads or e-matches with the main power rail.\
The board and all microcontrollers can be charged and programmed via a single USB-C receptacle. For programming, select a microcontroller using the short circuit headers which control the USB mux.\
Status is indicated using various LEDs and a buzzer.\
Accurate time is kept through an external 32.768 kHz oscillator powering the RTC of NAV.
