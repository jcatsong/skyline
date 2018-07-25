/*
  Sean Lee
  2018
*/

#include "gpio.h"
#include "uart.h"
#include "system.h"

int main(void){

  // Initialization functions
  initGPIO();
  initUART();
  initSysTick();

  // Work loop
  enableInterrupts();
  while(1){
    // Update Systick LED callback if necessary

    // Look for new UART packets

    // Check if we should run any commands based on UART

    // TODO Go back to low power mode (systick to wake up?)
  }

}
