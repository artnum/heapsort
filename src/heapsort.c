#include "include/heapsort.h"
#ifndef NDEBUG
#include <stdio.h>
#endif

static inline int _cmp(struct heapsort_ctx_t ctx, uint8_t *origin, size_t a,
                       size_t b) {
  switch (ctx.type) {
  case HEAPSORT_CMP_UINT8:
    return *(uint8_t *)(origin + (a * ctx.size) + ctx.offset) >
           *(uint8_t *)(origin + (b * ctx.size) + ctx.offset);
  case HEAPSORT_CMP_UINT16:
    return *(uint16_t *)(origin + (a * ctx.size) + ctx.offset) >
           *(uint16_t *)(origin + (b * ctx.size) + ctx.offset);
  case HEAPSORT_CMP_UINT32:
    return *(uint32_t *)(origin + (a * ctx.size) + ctx.offset) >
           *(uint32_t *)(origin + (b * ctx.size) + ctx.offset);
  case HEAPSORT_CMP_UINT64:
    return *(uint64_t *)(origin + (a * ctx.size) + ctx.offset) >
           *(uint64_t *)(origin + (b * ctx.size) + ctx.offset);
  case HEAPSORT_CMP_FLOAT:
    return *(float *)(origin + (a * ctx.size) + ctx.offset) >
           *(float *)(origin + (b * ctx.size) + ctx.offset);
  case HEAPSORT_CMP_DOUBLE:
    return *(double *)(origin + (a * ctx.size) + ctx.offset) >
           *(double *)(origin + (b * ctx.size) + ctx.offset);
  }
  return 0;
}

static inline void _swap(uint8_t *a, uint8_t *b, uint8_t *tmp, size_t size) {
#ifndef NDEBUG
  fprintf(stderr, "%p %p %p %ld\n", a, b, tmp, size);
#endif
  memmove(tmp, a, size);
  memmove(a, b, size);
  memmove(b, tmp, size);
}

static inline void _heapify(struct heapsort_ctx_t ctx, uint8_t *origin,
                            size_t rootnode, size_t length) {
  size_t largest;
  size_t left;
  size_t right;

__heapify:
  largest = rootnode;
  left = 2 * rootnode + 1;
  right = 2 * rootnode + 2;

  if (left < length && _cmp(ctx, origin, left, largest))
    largest = left;
  if (right < length && _cmp(ctx, origin, right, largest))
    largest = right;

  if (largest != rootnode) {
    _swap(origin + (rootnode * ctx.size), origin + (largest * ctx.size),
          ctx.tmp, ctx.size);
    rootnode = largest;
    goto __heapify;
  }
}

void heapsort(struct heapsort_ctx_t ctx, uint8_t *origin, size_t length) {
  for (size_t i = length / 2 - 1; i + 1 != 0; i--) {
    _heapify(ctx, origin, i, length);
  }
  for (size_t i = length - 1; i > 0; i--) {
    _swap(origin, origin + (ctx.size * i), ctx.tmp, ctx.size);
    _heapify(ctx, origin, 0, i);
  }
}
