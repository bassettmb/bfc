#include "io.h"
#include "exit.h"
#include "heap.h"

FILE *bfc_in;
FILE *bfc_out;

void
bfc_putc(ptrdiff_t offset)
{
  bfc_check_access(offset);
  if (putc(bfc_hp[offset], bfc_out) == EOF)
    bfc_panic();
}

void
bfc_getc(ptrdiff_t offset)
{
  bfc_check_access(offset);
  int ch = getc(bfc_in);
  if (ch != EOF)
    bfc_hp[offset] = ch;
  else if (!feof(bfc_in)) /* If we're not at EOF, something bad happened. */
    bfc_panic();
  else
    /* Otherwise, we leave the value on the other end of the heap pointer
     * untouched, clear the error and continue.
     */
    clearerr(bfc_in);
}

void
bfc_io_init(FILE *input, FILE *output)
{
  bfc_in = input ? input : stdin;
  bfc_out = output ? output : stdout;
}

void
bfc_io_deinit(int close_input, int close_output)
{
  if (close_input)
    fclose(bfc_in);
  bfc_in = 0;
  if (close_output)
    fclose(bfc_out);
  bfc_out = 0;
}
