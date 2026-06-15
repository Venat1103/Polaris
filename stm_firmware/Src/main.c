/*
 * main.c
 *
 *  Created on: 15-Jun-2026
 *      Author: soham
 */

#include <stdint.h>

//#if !defined(__SOFT_FP__) && defined(__ARM_FP)
//  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
//#endif

#include "stm32f412rx.h"

#include "main.h"

#define SCB_CPACR (*((volatile uint32_t *)0xE000ED88))

int main(void)
{
	SCB_CPACR |= (0xF << 20);  // Enable FPU
    /* Loop forever */
	for(;;);
}
