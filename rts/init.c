#include "heap.h"
#include "io.h"

void
bfc_init(FILE *input, FILE *output)
{
  bfc_heap_init();
  bfc_io_init(input, output);
}

void
bfc_deinit(int close_input, int close_output)
{
  bfc_heap_deinit();
  bfc_io_deinit(close_input, close_output);
}
