/*
  Circular buffer implementation
  Defined to store bytes, and full to mean tail == head - 1, wastes a slot
  but makes logic much easier.
*/
#include "buffer.h"

/*
  Initialize the buffer
*/
int bufferInit(circularBuf_t *cbuff){
  int status = -1;

  if(cbuff){
    cbuff->head = 0;
    cbuff->tail = 0;
    cbuff->size = BUFFER_SIZE;
    cbuff->count = 0;
    status = 0;
  }

  return status;
}

/*
  Calling functions should ensure buffer is not full, otherwise data
  is overwritten
*/
int bufferPut(circularBuf_t *cbuff, uint8_t data){
  int status = -1;

  // if(cbuff && !bufferFull(cbuff)){
  if(cbuff){
    cbuff->buffer[cbuff->head] = data;
    cbuff->head = (cbuff->head + 1) % cbuff->size;
    cbuff->count++;
    status = 0;
  }
  // else{
  // TODO: add error counter if buffer was full
  // }

  return status;
}

/*
  Only supplies data if buffer wasnt empty to begin with
*/
int bufferGet(circularBuf_t *cbuff, uint8_t *data){
  int status = -1;

  if(cbuff && data && !bufferEmpty(cbuff)){
    *data = cbuff->buffer[cbuff->tail];
    cbuff->tail = (cbuff->tail + 1) % cbuff->size;
    cbuff->count--;
    status = 0;
  }

  return status;
}

uint32_t bufferCount(circularBuf_t *cbuff){
  return cbuff->count;
}

uint32_t bufferRemain(circularBuf_t *cbuff){
  return ((cbuff->size - 1) - cbuff->count);
}

bool bufferEmpty(circularBuf_t *cbuff){
  return (cbuff->head == cbuff->tail);
}

bool bufferFull(circularBuf_t *cbuff){
  return (((cbuff->head + 1) % cbuff->size) == cbuff->tail);
}
