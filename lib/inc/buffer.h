#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE 64

typedef struct {
    uint8_t buffer[BUFFER_SIZE];
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t count;
} circularBuf_t;

int bufferInit(circularBuf_t *cbuff);

int bufferPut(circularBuf_t *cbuff, uint8_t data);

int bufferGet(circularBuf_t *cbuff, uint8_t *data);

uint32_t bufferCount(circularBuf_t *cbuff);

uint32_t bufferRemain(circularBuf_t *cbuff);

bool bufferEmpty(circularBuf_t *cbuff);

bool bufferFull(circularBuf_t *cbuff);
