/*
 * main.c
 *
 *  Created on: 15-Jun-2026
 *      Author: soham
 */

#include <stdint.h>
#include <stdbool.h>

#include "stm32f446xx.h"

#include "machine/fsm.h"
#include "main.h"
#include "machine/machine.h"

int main(void)
{
	// Start TIM2 as master clock, correct by RTC for drift
	tim2_1mhz_init();
	return 0;
}
