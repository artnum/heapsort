#ifndef HEAPSORT_H__
#define HEAPSORT_H__ 1

#include <stdint.h>
#include <string.h>

enum heapsort_cmp_type {
  HEAPSORT_CMP_UINT8,
  HEAPSORT_CMP_UINT16,
  HEAPSORT_CMP_UINT32,
  HEAPSORT_CMP_UINT64,
  HEAPSORT_CMP_FLOAT,
  HEAPSORT_CMP_DOUBLE
};

struct heapsort_ctx_t {
  size_t size;
  size_t offset;
  enum heapsort_cmp_type type;
  uint8_t *tmp;
};

void heapsort_sort(struct heapsort_ctx_t ctx, uint8_t *origin, size_t length);

#endif /* HEAPSORT_H__ */
