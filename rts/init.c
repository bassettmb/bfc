#include "heap.h"
#include "io.h"

void
bfc_init(FILE *input, FILE *output)
{
  bfc_heap_init();
  bfc_io_init(input, output);
}
