#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "buffer.h"

void static printTestName(char *name){
  printf("Starting test: %s\n", name);
}

void static finishTest(char *name){
  printf("Passed test: %s\n", name);
}

void testSimpleBuffer(void){
  char *testName = "testSimpleBuffer";
  int numToAdd = 10;

  printTestName(testName);
  circularBuf_t buf;
  bufferInit(&buf);
  uint8_t i;
  // Add 10 basic items
  for(i = 0; i < numToAdd; i++){
    bufferPut(&buf, i);
  }
  assert(buf.count == numToAdd);
}

void testRemoveAllItems(void){
  char *testName = "testRemoveAllItems";
  int numToAdd = 64;

  printTestName(testName);
  circularBuf_t buf;
  bufferInit(&buf);
  uint8_t i;
  // Add items
  for(i = 0; i < numToAdd; i++){
    bufferPut(&buf, i);
  }
  assert(buf.count == numToAdd - 1);
  // Remove items
  uint8_t data;
  for(i = 0; i < (numToAdd - 1); i++){
    bufferGet(&buf, &data);
    assert(data == i);
  }
  assert(buf.count == 0);
}

int main(void){
  // Tests
  printf("Running circular buffer tests\n");
  testSimpleBuffer();
  testRemoveAllItems();
  return 0;
}
