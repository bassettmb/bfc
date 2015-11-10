#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *bf_progname;
static uint8_t *bf_hp;
static size_t bf_heapsize;

void
bf_panic(void)
{
  fflush(stdout);
  perror(bf_progname);
  exit(EXIT_FAILURE);
}

void
bf_init(int argc, const char *const *argv)
{
  bf_progname = strdup(argv[0]);
  if (!bf_progname) {
    bf_progname = argv[0];
    bf_panic();
  }
}

void
bf_putc(int ch)
{
  putc(ch)

void
bf_grow_left(void)
{

