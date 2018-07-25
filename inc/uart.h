#include <stdint.h>
#include <stdbool.h>

// Defines for use in UART driver
#define UART_BAUD_DIV 833

/*
  0x4001 3800 base address for USART1
  0x4002 1000 base address for RCC
  USART1 on PA9 (TX) PA10(RX)
  8n1 9600
*/
void initUART();

/*
  Add the specified message to the UART Tx bufer
  returns: -1 if unable to bnuffer message, 0 if able
*/
int bufferMsg(char *msg);

/*
  Used by systick handler to start Tx messages if buffer isnt empty.
*/
void startUartTransfer();

/*
  Checks if UART Tx buffer is empty
*/
bool uartTxBufferEmpty();

/*
  Helper for USART1 Interrupt handler to move data out of ring buffer
*/
void uartPutChar();
