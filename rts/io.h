#ifndef BFC_RTS_IO_H
#define BFC_RTS_IO_H

#include "config.h"
#include <stddef.h>
#include <stdio.h>

BFC_RTS_EXPORT FILE *bfc_in;
BFC_RTS_EXPORT FILE *bfc_out;
void bfc_io_init(FILE *input, FILE *output);
BFC_RTS_EXPORT void bfc_putc(ptrdiff_t offset);
BFC_RTS_EXPORT void bfc_getc(ptrdiff_t offset);

#endif /* !BFC_RTS_IO_H */
