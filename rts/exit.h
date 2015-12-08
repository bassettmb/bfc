#ifndef BFC_RTS_EXIT_H
#define BFC_RTS_EXIT_H

#include "config.h"

/* Halt program execution, hopefully yielding the provided exit code
 * unless something goes really wrong.
 */
BFC_RTS_EXPORT void bfc_halt(int exit_code);

/* Print a diagnostic message from the current value of errno and halt. */
void bfc_panic(void);

#endif /* !BFC_RTS_EXIT_H */
