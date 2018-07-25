// States allowed
// typedef enum{
//   LOW = 0,
//   MID,
//   HIGH,
//   ABORT
// };

#define TEST_MSG "deadbeef"
#define SYSTICK_TICKS 1000

uint32_t initSysTick();

void enableInterrupts();

void getTickCount();

uint32_t getTimestamp();

void heartbeat();
