#ifndef BF_HEAP_H
#define BF_HEAP_H

#include "types.h"

register bf_cell *bf_hp asm("rdx");
void bf_heap_init(void);

#endif /* !BF_HEAP_H */
