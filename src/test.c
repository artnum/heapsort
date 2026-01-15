#include "include/heapsort.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 32

struct some_structure {
  int i;
  int j;
  uint16_t order;
  int x;
  int y;
};

int main(void) {
  srand(time(NULL));
  {
    struct some_structure tmp = {0};
    struct some_structure array[ARRAY_SIZE] = {0};
    struct heapsort_ctx_t ctx = {sizeof(struct some_structure),
                                 offsetof(struct some_structure, order),
                                 HEAPSORT_CMP_UINT16, (uint8_t *)&tmp};

    for (int i = 0; i < ARRAY_SIZE; i++) {
      array[i].order = rand() % 0xFFFF;
    }
    heapsort(ctx, (uint8_t *)array, ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
      printf("%d\n", array[i].order);
    }
    printf("\n");
  }

  {
    uint32_t tmp = 0;
    uint32_t array[ARRAY_SIZE] = {0};
    struct heapsort_ctx_t ctx = {sizeof(uint32_t), 0, HEAPSORT_CMP_UINT32,
                                 (uint8_t *)&tmp};
    for (int i = 0; i < ARRAY_SIZE; i++) {
      array[i] = rand() % 0xFFFFFFFF;
    }
    heapsort(ctx, (uint8_t *)array, ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
      printf("%d\n", array[i]);
    }
    printf("\n");
  }

  return 0;
}
