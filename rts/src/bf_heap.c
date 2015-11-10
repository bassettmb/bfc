#include <errno.h>
#include <sys/mman.h>

#define BF_BLOCKSIZE (4096ul)

uint8_t *base;


bf_heap_init(size_t nbytes)

void *
bf_alloc_heap(size_t nbytes)
{
  if (SIZE_MAX / BF_BLOCKSIZE < nblocks) {
    errno = ENOMEM;
    bf_panic();
  }

  mmap(
