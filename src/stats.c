#include "stdint.h"

#include "stats.h"

static stats_t statsCounter;

void initStats(){
  statsCounter.uartTxCount = 0;
  statsCounter.uartRxCount = 0;
  statsCounter.bufferFull = 0;
}

stats_t *getCounterPtr(void){
  return &statsCounter;
}
