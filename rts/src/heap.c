#include "debug.h"
#include "heap.h"

#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#include <sys/mman.h>

#define BF_HEAP_PROT (PROT_READ | PROT_WRITE)
#define BF_HEAP_MODE (MAP_PRIVATE | MAP_ANONYMOUS)

#define BF_MIN_GROW (1024u)
#define BF_MIN_HEAP (4096u)
#define BF_MIN_LEFT BF_MIN_GROW

register bf_cell *bf_hp asm("rdx");
static bf_cell *bf_hp_base;
static size_t bf_heap_size = BF_MIN_HEAP;

static size_t bf_need_left = BF_MIN_GROW;
static size_t bf_need_right = BF_MIN_GROW;

static size_t
bf_pagesize(void)
{
  static size_t pagesize;
  if (!pagesize) {
    long psize = sysconf(_SC_PAGE_SIZE);
    if (psize < 0)
      BF_PANIC_ERROR("could not determine vmem page size");
    pagesize = psize;
  }
  return pagesize;
}

static void *
bf_os_alloc(size_t nbytes)
{
  BF_ASSERT(nbytes % bf_pagesize() == 0);
  /* XXX: Windows support? ... or just use cygwin */
  void *mem = mmap(0, nbytes, BF_HEAP_PROT, BF_HEAP_MODE, -1, 0);
  if (mem == MAP_FAILED)
    BF_PANIC_ERROR("out of memory");
  return mem;
}

static void
bf_os_protect(void *ptr, size_t nbytes)
{
  BF_ASSERT(nbytes % bf_pagesize() == 0);
  if (mprotect(ptr, nbytes, PROT_NONE))
    BF_PANIC_ERROR("could not mark vmem page inaccessible");
}

static void
bf_os_dealloc(void *ptr, size_t nbytes)
{
  if (munmap(ptr, nbytes))
    BF_PANIC_ERROR("could not unmap vmem");
}

static bf_cell *
bf_heap_alloc(size_t nbytes)
{
  size_t pagesize = bf_pagesize(); /* size of a vmem page */

  /* How many pages do we need for the given alloc request? */

  size_t npages = nbytes / pagesize; /* full pages */
  npages += (nbytes % pagesize != 0); /* do we need a partial page? */
  npages += 2; /* add two pages for marking beginning and end (see below) */

  /* ensure we don't overflow */
  if (SIZE_MAX / pagesize < npages) {
    errno = ENOMEM;
    BF_PANIC_ERROR("out of memory");
  }

  size_t nalloc = pagesize * npages;
  void *mem = bf_os_alloc(nalloc);
  bf_os_protect(mem, pagesize);
  bf_os_protect(mem + (nalloc - pagesize), pagesize);
  return (bf_cell *)((char *)mem + pagesize);
}

bf_cell *
bf_heap_grow_left(bf_cell *ptr, size_t size, size_t need)
{
  /* check overflow */
  if (SIZE_MAX - size < need) {
    errno = ENOMEM;
    BF_PANIC_ERROR("out of memory");
  }

  void *mem = bf_heap_alloc(size + need);
  memcpy(mem + need, ptr, size);
  bf_os_dealloc(ptr, size);
  return mem;
}

bf_cell *
bf_heap_grow_right(bf_cell *ptr, size_t size, size_t need)
{
  if (SIZE_MAX - size < need) {
    errno = ENOMEM;
    BF_PANIC_ERROR("out of memory");
  }

  void *mem = bf_heap_alloc(size + need);
  memcpy(mem, ptr, size);
  bf_os_dealloc(ptr, size);
  return mem;
}

size_t
bf_next_size(size_t *size)
{
  BF_ASSERT(size);
  size_t cur = *size;
  if (SIZE_MAX / 2 < cur) {
    errno = ENOMEM;
    BF_PANIC_ERROR("out of memory");
  }
  cur *= 2;
  *size = cur;
  return cur;
}

void
bf_heap_grow(void *fault_ptr)
{
  if (fault_ptr == bf_hp_base - 1) {
    size_t need = bf_next_size(&bf_need_left);
    bf_hp_base = bf_heap_grow_left(bf_hp_base, bf_heap_size, need);
    bf_hp = bf_hp_base + (need - 1);
    bf_heap_size += need;
  } else if (fault_ptr == bf_hp_base + bf_heap_size) {
    size_t need = bf_next_size(&bf_need_right);
    bf_hp_base = bf_heap_grow_right(bf_hp_base, bf_heap_size, need);
    bf_hp = bf_hp_base + bf_heap_size;
    bf_heap_size += need;
  } else {
    BF_PANIC("unexpected segfault accessing: %p", fault_ptr);
  }
}

void
bf_segfault_handler(int signo, siginfo_t *si, void *ctx)
{
  if (signo != SIGSEGV && signo != SIGBUS)
    BF_PANIC("sigsegv handler responded to signal number %d", signo);
  BF_LOG("fault: %p", si->si_addr);
  BF_LOG("bf_hp_base: %p", bf_hp_base);
  BF_LOG("bf_hp_lim: %p", bf_hp_base + bf_heap_size);
  bf_heap_grow(si->si_addr);
}

void
bf_heap_init(void)
{
  bf_hp_base = bf_heap_alloc(bf_heap_size);
  struct sigaction sa;
  sa.sa_sigaction = bf_segfault_handler;
  sigfillset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART | SA_SIGINFO;
  if (sigaction(SIGSEGV, &sa, 0))
    BF_PANIC_ERROR("failed to install SIGSEGV signal handler");
  if (sigaction(SIGBUS, &sa, 0))
    BF_PANIC_ERROR("failed to install SIGBUS signal handler");
  bf_hp = bf_hp_base + BF_MIN_LEFT;
}
