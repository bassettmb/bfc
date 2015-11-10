#include "debug.h"
#include "heap.h"
#include <stddef.h>

int
main(void)
{
  bf_heap_init();
  for (size_t ix = 0; ix < (4096 - 1024) + 1; ix += 1) {
    bf_hp[ix] = 0;
    BF_LOG("wrote to %zu", ix);
  }
  return 0;
}
