/*
 * main.c
 *
 *  Created on: 15-Jun-2026
 *      Author: soham
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "stm32f446xx.h"

#include "main.h"

#include "peripherals/gpio.h"
#include "peripherals/rcc.h"
#include "peripherals/tim.h"
#include "peripherals/usart.h"

#include "machine/fsm.h"
#include "machine/machine.h"

////////////////////////////
// TIMER 2 INTERNAL CLOCK //
////////////////////////////

uint32_t micros() {
    return TIM2->CNT;
}

uint32_t millis() {
    return TIM2->CNT / 1000UL;
}

///////////////////
// DEBUG LOGGING //
///////////////////

#if defined(DEBUG_LOGGING)
    #include "com_port.h"

    char buffer1[512];
    char buffer2[512];

    uint32_t last_1 = 0;
    uint32_t last_05 = 0;
#endif

//////////
// MAIN //
//////////

int main() {
    #if defined(DEBUG_LOGGING)
        com_port_init(&buffer1[0]);
        sprintf(buffer1, "Debug logging started\r\n");
        com_port_transmit(buffer1);
        gpio_set_pin_mode(GPIOA, 5, GPIO_MODE_OUTPUT);
    #endif
    // Start TIM2 as master clock, correct by RTC for drift
    tim32_init(TIM2, TIM2_PRESCALAR, TIM2_AUTO_RELOAD_VALUE);
    while(1) {
        #if defined(DEBUG_LOGGING)
            if (millis() - last_1 >= 1000) {
                last_1 = millis();
                sprintf(buffer1, "TIM2 1 second task: %ld\r\n", millis());
                com_port_transmit(buffer1);
            } else if (millis() - last_05 >= 500) {
                last_05 = millis();
                sprintf(buffer2, "TIM2 0.5 second task: %ld\r\n", millis());
                com_port_transmit(buffer2);
                gpio_toggle(GPIOA, 5);
            }
        #endif
    }
    return 0;
}
