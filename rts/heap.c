#include "alloc.h"
#include "assert.h"
#include "heap.h"
#include "exit.h"

#include <errno.h>
#include <string.h>
#include <stdint.h>

#define BFC_UNIT (1UL) /* avoid integer overflow */

/* These are essentially arbitrary. */
#define BFC_INIT_HEAPSIZE (BFC_UNIT << 20)
#define BFC_HEAP_GROWTHFACTOR (2)

/* Reserve 1/8th the heap on the left-hand side under the assumption that
 * we'll be primarily expanding to the right.
 */
#define BFC_INIT_HEAPOFF (BFC_INIT_HEAPSIZE >> 3)
#define BFC_MIN_GROW (BFC_UNIT << 11)

#define BFC_ASSERT_HP_SANITY() do { \
  BFC_ASSERT(bfc_hp >= bfc_hp_base); \
  BFC_ASSERT(bfc_hp < bfc_hp_lim); \
} while(0)

/* *the* brainfuck heap pointer (the figurative cursor on the tape) */

bf_value *bfc_hp;

/* External but not exported symbols. */

void bfc_heap_init(void);
void bfc_check_access(ptrdiff_t offset);

/* Symbols internal to translation unit. */

/* recommend a new heap size */
static size_t bfc_heap_recommend(size_t min, size_t need, size_t max);

/* routines for ensuring we have count bytes either to the left or right */
static void bfc_heap_ensure_left(size_t count);
static void bfc_heap_ensure_right(size_t count);

/* Heap bookkeeping variables. */
static bf_value *bfc_hp_base; /* bottom of allocated memory */
static bf_value *bfc_hp_lim;  /* top of allocated memory */

/* Values by which ends of the heap were last grown. */
static size_t bfc_lgrow = BFC_MIN_GROW;
static size_t bfc_rgrow = BFC_MIN_GROW;

/* Function definitions */

size_t
bfc_heap_recommend(size_t min, size_t need, size_t max)
{
  while (min <= need) {
    if (max / BFC_HEAP_GROWTHFACTOR < min) {
      errno = ENOMEM;
      bfc_panic();
    }
    min *= BFC_HEAP_GROWTHFACTOR;
  }

  return min;
}

void
bfc_heap_ensure_left(size_t count)
{
  /* we assume bfc_hp always points to memory we own */
  BFC_ASSERT_HP_SANITY();

  /* space available to the left of the heap pointer */
  size_t avail = bfc_hp - bfc_hp_base;

  /* If our available space exceeds our constraint, we're done. Otherwise,
   * we need to grow the heap.
   */
  if (avail >= count)
    return; /* bfc_hp - count is valid */

  size_t size = bfc_hp_lim - bfc_hp_base;
  size_t grow = bfc_heap_recommend(bfc_lgrow, count - avail, SIZE_MAX - size);
  BFC_ASSERT(SIZE_MAX - size >= grow);
  size_t newsize = size + grow;

  bf_value *newheap = bfc_realloc(bfc_hp_base, newsize);
  BFC_ASSERT(newheap);

  memset(newheap, 0, grow);
  bfc_hp = newheap + (bfc_hp - bfc_hp_base) + grow;
  bfc_hp_base = newheap;
  bfc_hp_lim = newheap + newsize;
  bfc_lgrow = grow;
}

void
bfc_heap_ensure_right(size_t count)
{
  /* we assume bfc_hp always points to memory we own */
  BFC_ASSERT_HP_SANITY();

  /* space available to the right of the heap pointer */
  size_t avail = bfc_hp_lim - bfc_hp;

  /* If our available space exceeds our constraint, we're done. Otherwise,
   * we need to grow the heap.
   */
  if (avail > count)
    return; /* bfc_hp + count is valid */

  size_t size = bfc_hp_lim - bfc_hp_base;
  size_t grow = bfc_heap_recommend(bfc_rgrow, count - avail, SIZE_MAX - size);
  BFC_ASSERT(SIZE_MAX - size >= grow);
  size_t newsize = size + grow;

  bf_value *newheap = bfc_realloc(bfc_hp_base, newsize);
  BFC_ASSERT(newheap);

  memset(newheap + size, 0, grow);
  bfc_hp = newheap + (bfc_hp - bfc_hp_base);
  bfc_hp_base = newheap;
  bfc_hp_lim = newheap + newsize;
  bfc_rgrow = grow;
}

void
bfc_heap_init(void)
{
  bfc_hp_base = bfc_realloc(bfc_hp, BFC_INIT_HEAPSIZE);
  /* bfc_realloc should not be capable of returning a null pointer here */
  BFC_ASSERT(bfc_hp_base);
  bfc_hp = bfc_hp_base + BFC_INIT_HEAPOFF;
  bfc_hp_lim = bfc_hp_base + BFC_INIT_HEAPSIZE;
}

void
bfc_heap_deinit(void)
{
  bfc_free(bfc_hp_base);
  bfc_hp_base = 0;
  bfc_hp = 0;
  bfc_hp_lim = 0;
}

void
bfc_check_access(ptrdiff_t offset)
{
  if (offset < 0) {
    /* Special case for 2's complement.
     * Realistically this shouldn't happen, but eh..
     */
    if (offset == PTRDIFF_MIN)
      bfc_heap_ensure_left((size_t)(-(offset + 1)) + 1);
    else
      bfc_heap_ensure_left((size_t)(-offset));
  } else {
    bfc_heap_ensure_right((size_t)offset);
  }
}
