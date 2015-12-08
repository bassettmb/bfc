#ifndef BFC_RTS_IO_H
#define BFC_RTS_IO_H

#include "config.h"
#include <stddef.h>
#include <stdio.h>

BFC_RTS_EXPORT FILE *bfc_in;
BFC_RTS_EXPORT FILE *bfc_out;
BFC_RTS_EXPORT void bfc_putc(ptrdiff_t offset);
BFC_RTS_EXPORT void bfc_getc(ptrdiff_t offset);
void bfc_io_init(FILE *input, FILE *output);
void bfc_io_deinit(int close_input, int close_output);

#endif /* !BFC_RTS_IO_H */
