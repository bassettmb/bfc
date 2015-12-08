#include "alloc.h"
#include "exit.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

void *
bfc_realloc(void *ptr, size_t nbytes)
{
  if (!nbytes) {
    free(ptr);
    return 0;
  }

  ptr = realloc(ptr, nbytes);
  if (!ptr)
    bfc_panic();
  return ptr;
}

void *
bfc_malloc(size_t nbytes)
{
  return bfc_realloc(0, nbytes);
}

void
bfc_free(void *ptr)
{
  (void)bfc_realloc(ptr, 0);
}
