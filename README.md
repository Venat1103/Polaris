# Polaris
Open source flight computer
##  High-Level Flight Computer Architecture
![Polaris System architecture](./images/Polaris.svg)

## 1. Power:
The whole system is powered by a single 2S Li-Po battery that can be charged via USB-C PD.
- Main Power Rail: 7.4-8.4V from battery or 9V from USB-C PD
- Battery charger IC: Texas Instruments BQ24005
- 5V regulator (switching): Texas Instruments LMR51430
- 3.3V regulator (linear): Texas Instruments TLV75733
- 3.3V RF regulator (linear): Texas Instruments TPS7A2033
- USB-PD negotiation: WCH CH224K
## 2. Processing:
- The board is powered by an STM32F446VE (NAV)
This is a 180 MHz MCU based on the ARM Cortex-M4
## 3. Sensors:
All connected to NAV only
- IMUs:
	- Main IMU: TDK InvenSense ICM42688-P
	- High-G Accelerometer: ST Microelectronics LSM6DSO32
- Barometric Pressure Sensors:
	- TE Connectivity MS5607-02BA03
	- ST Microelectronics LPS22HHTR
- GNSS Module: u-blox GPS NEO-7M

I used the LSM6DSO32 since dedicated high-G accelerometers were either unavailable or too expensive.\
I used two barometers for redundancy.\
I wanted to use the newer GPS NEO-M8N instead of the NEO-7M since it has reached EoL. Unfortunately it is out of stock wherever I search, or is four times any reasonable price.
## 4. Communication and Logging:
All sensor and calculated data is communicated through/logged to:
- Telemetry:
	- Wireless Radio: Ai-Thinker Ra-08H
- Logging:
	- MicroSD Card slot
	- Winbond W25Q128JVE 16 MB flash
The Ra-08H is a fairly cheap LoRa module based on the ASR6601 SoC
## 5. Active Control:
Active control is achieved through 6 servo lines controlled via PWM signals from NAV. \
The board supports both thrust vector control and fin control. \
These lines can be split up in any which way. \
The servos must be high-power and operate at up to 9V, since their power rail will be connected directly to the (up to) 8.4V of the battery \
Power supplied to the active control servos is controlled through an XT-60 terminal. When active control is needed, plug this terminal with a short-circuit cap, making sure that the cap can withstand the current drawn by the servos. In case the active control system is not in the best condition to operate at launch, this provides an easy way to cut off the system so that the rocket can still launch
## 6. Others:
The board supports firing the motor and all parachutes using firing leads or e-matches with the main power rail.\
The board and all microcontrollers can be charged and programmed via a single USB-C receptacle. For programming, select a microcontroller using the short circuit headers which control the USB mux.\
Status is indicated using various LEDs and a buzzer.\
Accurate time is kept through an external 32.768 kHz oscillator powering the RTC of NAV.
