#include <stdbool.h>

#include "stm32f0xx.h"
#include "cmsis_gcc.h"

#include "uart.h"
#include "stats.h"
#include "buffer.h"

static circularBuf_t uartTxBuffer;

/********************************************
Private function declarations
*********************************************/
static uint32_t strlen(char *s){
  uint32_t length = 0;
  while(*s++){
    length++;
  }
  return length;
}

/********************************************
Public function declarations
*********************************************/
void uartPutChar(){
  uint8_t data;
  bufferGet(&uartTxBuffer, &data);
  USART1->TDR = data;
}

void initUART(){
  // Configured GPIOA 9&10 for UART
  // Enable clock to port A APB2 for UART
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  RCC->APB2ENR |= (RCC_APB2ENR_USART1EN);
  // Alternate function, push-pull w/pull-up, speed slow
  GPIOA->MODER |= ((2 << GPIO_MODER_MODER9_Pos) | (2 << GPIO_MODER_MODER10_Pos));
  GPIOA->OTYPER |= ((1 << GPIO_MODER_MODER9_Pos) | (1 << GPIO_MODER_MODER10_Pos));
  GPIOA->OSPEEDR &= (~(3 << GPIO_MODER_MODER9_Pos) | ~(3 << GPIO_MODER_MODER9_Pos));
  GPIOA->AFR[1] |= (1 << GPIO_AFRH_AFSEL9_Pos) | (1 << GPIO_AFRH_AFSEL10_Pos);
  GPIOA->PUPDR |= ((1 << GPIO_MODER_MODER9_Pos) | (1 << GPIO_MODER_MODER10_Pos));

  // Disable UART during programming
  USART1->CR1 = 0;

  // 8n1, 9600
  USART1->BRR = UART_BAUD_DIV;
  USART1->CR2 = 0;
  USART1->CR3 = 0;

  // Enable receiver and Transmitter
  USART1->CR1 |= (USART_CR1_RE | USART_CR1_TE);

  // Enable DMA transfers to the UART
  USART1->CR3 |= USART_CR3_DMAT;

  // Enable interrupts from UART, clear the TXE bit in case its somehow already set
  CLEAR_BIT(USART1->ISR, USART_ISR_TXE);
  NVIC_EnableIRQ(USART1_IRQn);
  NVIC_SetPriority(USART1_IRQn, 4);

  // Initialize the buffers
  bufferInit(&uartTxBuffer);

  // Enable USART
  USART1->CR1 |= USART_CR1_UE;
}

int bufferMsg(char *msg){
  if((strlen(msg) + 2) > bufferRemain(&uartTxBuffer)){
    return -1;
  }
  else{
    // Add the message string itself
    while(*msg){
        bufferPut(&uartTxBuffer, *msg);
        msg++;
    }
    // Add end message
    bufferPut(&uartTxBuffer, '\r');
    bufferPut(&uartTxBuffer, '\n');
    return 0;
  }
}

bool uartTxBufferEmpty(){
  return bufferEmpty(&uartTxBuffer);
}

void startUartTransfer(){
  // Enable TXE interrupts from UART
  USART1->CR1 |= USART_CR1_TXEIE;
}
