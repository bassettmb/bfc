#include "bfc_rts.h"
#include <stdlib.h>

extern void bfc_main(void);

int
main(void)
{
  /* Initialize rts */
  bfc_init(0, 0); /* set input & output streams to default values */
  bfc_main(); /* enter compiled code */
  bfc_deinit(0, 0); /* shut down the rts */
  bfc_halt(EXIT_SUCCESS);
  return 0;
}
