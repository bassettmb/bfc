#include "assert.h"
#include "exit.h"
#include "io.h"
#include <stdlib.h>

void
bfc_assert_fail(const char *file, const char *fn, int line, const char *expr)
{
  if (bfc_out)
    fflush(bfc_out);
  fprintf(stderr, BFC_RTS_NAME ": %s:%s:%d: assertion failed: '%s'\n",
          file, fn, line, expr);
  fflush(stderr);
  bfc_halt(EXIT_FAILURE);
}
