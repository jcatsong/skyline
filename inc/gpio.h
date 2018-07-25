/*
  GPIO related functions
*/
#ifndef GPIO_H
#define GPIO_H

#include <stdio.h>

#define ledBlue 8
#define ledGreen 9

void initGPIO();

void toggleGPIO(uint32_t gpioSelect);

#endif
