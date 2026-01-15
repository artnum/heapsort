#include "include/heapsort.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 32

struct some_structure {
  int i;
  int j;
  uint16_t order;
  int x;
  int y;
};

int main(int argc, char **argv) {
  struct some_structure tmp = {0};
  struct some_structure array[ARRAY_SIZE] = {0};
  struct heapsort_ctx_t ctx = {sizeof(struct some_structure),
                               offsetof(struct some_structure, order),
                               HEAPSORT_CMP_UINT16, (uint8_t *)&tmp};

  for (int i = 0; i < ARRAY_SIZE; i++) {
    array[i].order = rand() % 0xFFFF;
  }

  heapsort_sort(ctx, (uint8_t *)array, ARRAY_SIZE);

  for (int i = 0; i < ARRAY_SIZE; i++) {
    printf("%d\n", array[i].order);
  }
  printf("\n");

  return 0;
}
