#include "include/heapsort.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 5000

struct some_structure {
  int i;
  int j;
  uint16_t order;
  int x;
  int y;
  void *ptr;
  uint32_t aasfdasd[54];
};

int main(void) {
  srand(time(NULL));
  {
    struct some_structure tmp = {0};
    struct some_structure array[ARRAY_SIZE + 1] = {0};
    struct heapsort_ctx_t ctx = {sizeof(struct some_structure),
                                 offsetof(struct some_structure, order),
                                 HEAPSORT_CMP_UINT16, (uint8_t *)&tmp};

    for (int i = 0; i < ARRAY_SIZE; i++) {
      array[i].order = rand() % 0xFFFF;
    }
    array[ARRAY_SIZE].i = 0xA0B1C2D3;
    heapsort(ctx, (uint8_t *)array, ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
      printf("%d\n", array[i].order);
    }
    printf("%x\n", array[ARRAY_SIZE].i);
  }

  {
    uint32_t tmp = 0;
    uint32_t array[ARRAY_SIZE + 1] = {0};
    struct heapsort_ctx_t ctx = {sizeof(uint32_t), 0, HEAPSORT_CMP_UINT32,
                                 (uint8_t *)&tmp};
    for (int i = 0; i < ARRAY_SIZE; i++) {
      array[i] = rand() % 0xFFFFFFFF;
    }
    array[ARRAY_SIZE] = 0xA0B1C2D3;
    heapsort(ctx, (uint8_t *)array, ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
      printf("%d\n", array[i]);
    }
    printf("%x\n", array[ARRAY_SIZE]);
  }

  return 0;
}
