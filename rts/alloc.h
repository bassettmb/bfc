#ifndef BFC_RTS_ALLOC_H
#define BFC_RTS_ALLOC_H

#include "config.h"
#include <stddef.h>

/* Allocation routines. For custom allocation schemes, manipulate
 * bfc_realloc since the other two call into that. Make sure bfc_realloc
 * frees the provided pointer when requested allocation size is 0.
 *
 * These functions should not fail. By default, they bail out via bfc_panic.
 */
BFC_RTS_EXPORT void *bfc_realloc(void *ptr, size_t nbytes);
BFC_RTS_EXPORT void *bfc_malloc(size_t nbytes);
BFC_RTS_EXPORT void bfc_free(void *ptr);

#endif /* !BFC_RTS_ALLOC_H */
