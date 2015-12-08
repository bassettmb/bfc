#ifndef BFC_RTS_INIT_H
#define BFC_RTS_INIT_H

#include "config.h"
#include <stdio.h>

BFC_RTS_EXPORT void bfc_init(FILE *input, FILE *output);
BFC_RTS_EXPORT void bfc_deinit(int close_input, int close_output);

#endif /* !BFC_RTS_INIT_H */
