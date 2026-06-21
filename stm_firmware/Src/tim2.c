#include "stm32f446xx.h"
#include "main.h"

#define RCC_APB1ENR_TIM2_ENABLE (1U)
#define RCC_TIM3_ENABLE (1U << 1)

#define TIM2_PRESCALAR 16 // 1 us per tick
#define TIM2_AUTO_RELOAD_VALUE 1000000
#define TIM2_CR1_ENABLE (1U)
#define TIM2_SR_UIF (1U)
#define TIM2_DIER_UIE_ENABLE (1U << 0)

void tim2_1mhz_init(void)
{
	// enable clock access
    RCC->APB1ENR |= RCC_APB1ENR_TIM2_ENABLE;
    // set prescalar
    TIM2->PSC = TIM2_PRESCALAR - 1;
    // set autoreload
    TIM2->ARR = TIM2_AUTO_RELOAD_VALUE - 1;

    // enable update interrupt
    TIM2->DIER |= TIM2_DIER_UIE_ENABLE;
    NVIC_EnableIRQ(TIM2_IRQn);

    // clear counter
    TIM2->CNT = 0;
    // enable
    TIM2->CR1 = TIM2_CR1_ENABLE;
}

