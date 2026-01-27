#include "include/heapsort.h"
#include <assert.h>
#include <stdint.h>
#include <string.h>

static inline int _cmp(struct heapsort_ctx_t ctx, uint8_t *origin, size_t a,
                       size_t b) {
  if (ctx.direction == HEAPSORT_DIR_DESC) {
    size_t t = a;
    a = b;
    b = t;
  }
  uint8_t *tmp_a = origin + (a * ctx.size) + ctx.offset;
  uint8_t *tmp_b = origin + (b * ctx.size) + ctx.offset;
  if (ctx.indirect != 0) {
    tmp_a = (uint8_t *)*(uintptr_t *)(origin + (a * ctx.size)) + ctx.offset;
    tmp_b = (uint8_t *)*(uintptr_t *)(origin + (b * ctx.size)) + ctx.offset;
    for (int i = ctx.indirect - 1; i > 0; i--) {
      tmp_a = (uint8_t *)*(uintptr_t *)tmp_a;
      tmp_b = (uint8_t *)*(uintptr_t *)tmp_b;
      if (tmp_a == NULL && tmp_b == NULL) {
        return 0;
      }
      if (tmp_a == NULL && tmp_b != NULL) {
        return 0;
      }
      if (tmp_a != NULL && tmp_b == NULL) {
        return 1;
      }
    }
  }
  switch (ctx.type) {
  case HEAPSORT_CMP_UINT8:
    return *(uint8_t *)tmp_a > *(uint8_t *)tmp_b;
  case HEAPSORT_CMP_UINT16:
    return *(uint16_t *)tmp_a > *(uint16_t *)tmp_b;
  case HEAPSORT_CMP_UINT32:
    return *(uint32_t *)tmp_a > *(uint32_t *)tmp_b;
  case HEAPSORT_CMP_UINT64:
    return *(uint64_t *)tmp_a > *(uint64_t *)tmp_b;
  case HEAPSORT_CMP_FLOAT:
    return *(float *)tmp_a > *(float *)tmp_b;
  case HEAPSORT_CMP_DOUBLE:
    return *(double *)tmp_a > *(double *)tmp_b;
  case HEAPSORT_CMP_STRING:
    return strcmp((const char *)tmp_a, (const char *)tmp_b) > 0;
  case HEAPSORT_CMP_CASE_STRING:
    return strcasecmp((const char *)tmp_a, (const char *)tmp_b) > 0;
  }
  return 0;
}

static inline void _swap(struct heapsort_ctx_t ctx, uint8_t *a, uint8_t *b) {
  if (ctx.indirect != 0) {
    uintptr_t tmp = 0;
    tmp = *(uintptr_t *)a;
    *(uintptr_t *)a = *(uintptr_t *)b;
    *(uintptr_t *)b = tmp;
  } else {
    memcpy(ctx.tmp, a, ctx.size);
    memcpy(a, b, ctx.size);
    memcpy(b, ctx.tmp, ctx.size);
  }
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
    _swap(ctx, origin + (rootnode * ctx.size), origin + (largest * ctx.size));
    rootnode = largest;
    goto __heapify;
  }
}

void heapsort(struct heapsort_ctx_t ctx, uint8_t *origin, size_t length) {
  assert(origin != NULL);
  assert(!((ctx.tmp == NULL || ctx.size == 0) && ctx.indirect == 0));

  if (ctx.indirect != 0) {
    ctx.size = sizeof(uintptr_t);
  }

  for (size_t i = length / 2 - 1; i + 1 != 0; i--) {
    _heapify(ctx, origin, i, length);
  }
  for (size_t i = length - 1; i > 0; i--) {
    _swap(ctx, origin, origin + (ctx.size * i));
    _heapify(ctx, origin, 0, i);
  }
}
