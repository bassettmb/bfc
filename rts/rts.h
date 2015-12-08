#ifndef BFC_RTS_H
#define BFC_RTS_H

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

typedef uint8_t bf_value;

extern bf_value *bfc_hp;

void bfc_init(FILE *input, FILE *output);
void bfc_deinit(int close_input, int close_output);

void bfc_check_access(ptrdiff_t offset);

/* Stolen from arith.h. */

#define bfc_add(off, val) (bfc_check_access(off), bfc_hp[(off)] += (val))
#define bfc_sub(off, val) (bfc_check_access(off), bfc_hp[(off)] -= (val))
#define bfc_mov(off) (bfc_check_access(off), bfc_hp += (off))
#define bfc_mul(off, val) (bfc_check_access(off), \
                           bfc_hp[(off)] += *bfc_hp * (val), *bfc_hp = 0)

void bfc_getc(ptrdiff_t offset);
void bfc_putc(ptrdiff_t offset);

void *bfc_realloc(void *ptr, size_t nbytes);
void *bfc_malloc(size_t nbytes);
void bfc_free(void *ptr);

void bfc_halt(int exit_code);


#endif /* !BFC_RTS_H */
