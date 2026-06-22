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

#include "machine/fsm.h"
#include "main.h"
#include "machine/machine.h"

#if defined(DEBUG_LOGGING)
	#include "com_port.h"

	void print(char *ch) {
		int i = 0;
		while (ch[i] != '\0') {
			usart2_write(ch[i]);
			i++;
		}
		return;
	}

	char buffer[512];
#endif

int main(void)
{
	#if defined(DEBUG_LOGGING)
		usart2_init();
		sprintf(buffer, "Debug logging started\r\n");
        print(buffer);
	#endif
	// Start TIM2 as master clock, correct by RTC for drift
	tim2_1mhz_init();
	return 0;
}
