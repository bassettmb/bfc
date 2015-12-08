#include "exit.h"
#include <stdio.h>
#include <stdlib.h>

void
bfc_halt(int exit_code)
{
  exit(exit_code);
  for (;;) {
    exit(EXIT_FAILURE);
    abort();
  }
}

void
bfc_panic(void)
{
  fflush(stdout);
  perror(BFC_RTS_NAME);
  fflush(stderr);
  bfc_halt(EXIT_FAILURE);
}
