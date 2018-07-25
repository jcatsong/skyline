typedef struct Statistics{
  uint32_t uartTxCount;
  uint32_t uartRxCount;
  uint8_t bufferFull;
}stats_t;

void initStats();

stats_t *getCounterPtr(void);
