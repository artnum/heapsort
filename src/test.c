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
  uint8_t *ptr1;
  uint16_t order;
  int x;
  char *ptr;
  int y;
  uint32_t aasfdasd[54];
  char string[64];
};

int main(void) {
  srand(time(NULL));
  {
    struct some_structure tmp = {0};
    struct some_structure array[ARRAY_SIZE + 1] = {0};
    struct heapsort_ctx_t ctx = {sizeof(struct some_structure),
                                 offsetof(struct some_structure, order),
                                 HEAPSORT_CMP_UINT16,
                                 HEAPSORT_DIR_ASC,
                                 0,
                                 (uint8_t *)&tmp};

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
    struct heapsort_ctx_t ctx = {sizeof(uint32_t),  0, HEAPSORT_CMP_UINT32,
                                 HEAPSORT_DIR_DESC, 0, (uint8_t *)&tmp};
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

  {
    uint32_t *array[ARRAY_SIZE + 1] = {0};
    struct heapsort_ctx_t ctx = {0, 0,   HEAPSORT_CMP_UINT32, HEAPSORT_DIR_ASC,
                                 1, NULL};
    for (int i = 0; i < ARRAY_SIZE; i++) {
      array[i] = malloc(sizeof(uint32_t));
      *array[i] = rand() % 0xFFFFFFFF;
    }
    heapsort(ctx, (uint8_t *)array, ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
      printf("%d\n", *array[i]);
      free(array[i]);
    }

    {
      struct some_structure *array[ARRAY_SIZE] = {0};
      struct heapsort_ctx_t ctx = {0,
                                   offsetof(struct some_structure, order),
                                   HEAPSORT_CMP_UINT16,
                                   HEAPSORT_DIR_ASC,
                                   1,
                                   NULL};
      for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = malloc(sizeof(struct some_structure));
        array[i]->order = rand() % 0xFFFF;
      }
      heapsort(ctx, (uint8_t *)array, ARRAY_SIZE);
      for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d\n", array[i]->order);
        free(array[i]);
      }
    }

    {
      const char *alpha =
          "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
      struct some_structure *array[ARRAY_SIZE] = {0};
      struct heapsort_ctx_t ctx = {0,
                                   offsetof(struct some_structure, string),
                                   HEAPSORT_CMP_STRING,
                                   HEAPSORT_DIR_ASC,
                                   1,
                                   NULL};
      for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = malloc(sizeof(struct some_structure));
        size_t slen = (rand() % 62) + 1;
        memset(array[i]->string, 0, 64);
        for (size_t j = 0; j < slen; j++) {
          array[i]->string[j] = alpha[rand() % strlen(alpha)];
        }
      }
      heapsort(ctx, (uint8_t *)array, ARRAY_SIZE);
      for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%s\n", array[i]->string);
        free(array[i]);
      }
    }
    {
      const char *alpha =
          "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
      struct some_structure *array[ARRAY_SIZE] = {0};
      struct heapsort_ctx_t ctx = {0,
                                   offsetof(struct some_structure, ptr),
                                   HEAPSORT_CMP_STRING,
                                   HEAPSORT_DIR_ASC,
                                   2,
                                   NULL};
      for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = malloc(sizeof(struct some_structure));
        size_t slen = (rand() % 62) + 1;
        array[i]->ptr = malloc(slen + 1);
        memset(array[i]->ptr, 0, slen + 1);
        for (size_t j = 0; j < slen; j++) {
          array[i]->ptr[j] = alpha[rand() % strlen(alpha)];
        }
      }
      heapsort(ctx, (uint8_t *)array, ARRAY_SIZE);
      for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%s\n", array[i]->ptr);
        free(array[i]->ptr);
        free(array[i]);
      }
    }
  }
  {
    struct some_structure *array[ARRAY_SIZE] = {0};
    struct heapsort_ctx_t ctx = {0,
                                 offsetof(struct some_structure, ptr1),
                                 HEAPSORT_CMP_UINT8,
                                 HEAPSORT_DIR_ASC,
                                 2,
                                 NULL};
    for (int i = 0; i < ARRAY_SIZE; i++) {
      array[i] = malloc(sizeof(struct some_structure));
      array[i]->ptr1 = malloc(sizeof(uint8_t));
      *array[i]->ptr1 = rand() % 0xFF;
    }
    heapsort(ctx, (uint8_t *)array, ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
      printf("%d\n", *array[i]->ptr1);
      free(array[i]->ptr1);
      free(array[i]);
    }
  }

  {
    struct some_structure *array[ARRAY_SIZE] = {0};
    struct heapsort_ctx_t ctx = {0,
                                 offsetof(struct some_structure, ptr1),
                                 HEAPSORT_CMP_UINT8,
                                 HEAPSORT_DIR_DESC,
                                 2,
                                 NULL};
    for (int i = 0; i < ARRAY_SIZE; i++) {
      array[i] = malloc(sizeof(struct some_structure));
      if (rand() % 2) {
        array[i]->ptr1 = NULL;
      } else {
        array[i]->ptr1 = malloc(sizeof(uint8_t));
        *array[i]->ptr1 = rand() % 0xFF;
      }
    }
    heapsort(ctx, (uint8_t *)array, ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
      printf("%d\n", array[i]->ptr1 == NULL ? -1 : *array[i]->ptr1);
      free(array[i]->ptr1);
      free(array[i]);
    }
  }
  {
    struct some_structure *array[ARRAY_SIZE] = {0};
    struct heapsort_ctx_t ctx = {0,
                                 offsetof(struct some_structure, ptr1),
                                 HEAPSORT_CMP_UINT8,
                                 HEAPSORT_DIR_ASC,
                                 2,
                                 NULL};
    for (int i = 0; i < ARRAY_SIZE; i++) {
      array[i] = malloc(sizeof(struct some_structure));
      if (rand() % 2) {
        array[i]->ptr1 = NULL;
      } else {
        array[i]->ptr1 = malloc(sizeof(uint8_t));
        *array[i]->ptr1 = rand() % 0xFF;
      }
    }
    heapsort(ctx, (uint8_t *)array, ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
      printf("%d\n", array[i]->ptr1 == NULL ? -1 : *array[i]->ptr1);
      free(array[i]->ptr1);
      free(array[i]);
    }
  }
  return 0;
}
