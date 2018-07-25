#include "core_cm0.h"
#include "cmsis_gcc.h"

#include "system.h"
#include "gpio.h"
#include "uart.h"

static volatile uint32_t tickCount = 0;
static uint32_t timestamp = 0;

/*
  Initialize various system related parameters, mainly Systick and other
  interrupts.
  Systick is configured to 1ms
*/
uint32_t initSysTick(){
  if (!SysTick_Config(SystemCoreClock / 1000)){
    return 0;
  }
  NVIC_EnableIRQ(SysTick_IRQn);
  return 1;
}

/*
  Enable interrupts for the processor as a whole
*/
void enableInterrupts(){
  __enable_irq();
}

/*

*/
uint32_t getTimestamp(){
  return timestamp;
}

/*

*/
void heartbeat(){
  timestamp++;
  // Always check for messages as someone else might have put data in the buffer
  if(!uartTxBufferEmpty()){
    startUartTransfer();
  }
  if(++tickCount == 1000){
    tickCount = 0;
    toggleGPIO(8);
    bufferMsg(TEST_MSG);
  }
}
