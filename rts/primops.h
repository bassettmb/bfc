#ifndef BFC_RTS_ARITH_H
#define BFC_RTS_ARITH_H

#include "heap.h"

#define bfc_add(off, val) (bfc_check_access(off), bfc_hp[(off)] += (val))
#define bfc_sub(off, val) (bfc_check_access(off), bfc_hp[(off)] -= (val))
#define bfc_mov(off) (bfc_check_access(off), bfc_hp += (off))
#define bfc_mul(off, val) (bfc_check_access(off), \
                           bfc_hp[(off)] += *bfc_hp * (val), *bfc_hp = 0)
#define bfc_set(off, val) (bfc_check_access(off), bfc_hp[(off)] = (val))

#endif /* !BFC_RTS_ARITH_H */
