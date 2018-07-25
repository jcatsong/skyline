#include "stm32f0xx.h"
#include "gpio.h"

/*
  Initialize the following GPIOs

  LEDs
    PC8 -> Blue
    PC9 -> Green
  User Button
    PA0
*/
void initGPIO(){
  // volatile uint32_t base_gpioc = GPIOC_BASE;

  // Enable clocks to port A and C
  RCC->AHBENR |= (RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN);

  // GPIOC configuration
  // P8/9 output
  GPIOC->MODER |= (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0);
  // PC8/9 output mode
  GPIOC->OTYPER &= ~(GPIO_OTYPER_OT_8 | GPIO_OTYPER_OT_9);
  // PC8/9 low speed
  GPIOC->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEEDR8 | GPIO_OSPEEDR_OSPEEDR9);
  // PC8/8 pull up/down disabled
  GPIOC->PUPDR &= (GPIO_PUPDR_PUPDR8 | GPIO_PUPDR_PUPDR9);
  // PC8/9 default high
  GPIOC->ODR |= (GPIO_ODR_8 | GPIO_ODR_9);

  // GPIOA configuration
  // P0 input
  GPIOA->MODER &= ~(GPIO_MODER_MODER0);
  // // Pulldown PA0 (done in HW?)
  // GPIOA->GPIO_PUPDR |= GPIO_PUPDR_PUPDR0_0;
  // EXTI0 map to PA0
  SYSCFG->CFGR1 &= ~(SYSCFG_EXTICR1_EXTI0_Msk);
  EXTI->RTSR |= EXTI_RTSR_TR0;
}

/*
  Toggle the selected GPIO
    0 -> PC8
    1 -> PC9
*/
void toggleGPIO(uint32_t gpioSelect){
  switch (gpioSelect){
    case 8:
      TOGGLE_BIT(GPIOC->ODR, GPIO_ODR_8);
      break;
    case 9:
      TOGGLE_BIT(GPIOC->ODR, GPIO_ODR_9);
      break;
  }
}
