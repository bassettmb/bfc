#ifndef BFC_RTS_HEAP_H
#define BFC_RTS_HEAP_H

#include "config.h"
#include "types.h"
#include <stddef.h>

BFC_RTS_EXPORT extern bf_value *bfc_hp;
BFC_RTS_EXPORT void bfc_check_access(ptrdiff_t offset);
void bfc_heap_init(void);
void bfc_heap_deinit(void);

#endif /* !BFC_RTS_HEAP_H */
