#ifndef BFC_RTS_ASSERT_H
#define BFC_RTS_ASSERT_H

#include "config.h"
#include "exit.h"

#define BFC_STRINGIFY_EXPAND(e) #e
#define BFC_STRINGIFY(e) BFC_STRINGIFY_EXPAND(e)

#ifndef NDEBUG
# define BFC_ASSERT(expr) \
    ((void)((expr) ? (void)(0) : \
        bfc_assert_fail(__FILE__, __func__, __LINE__, BFC_STRINGIFY(expr))))
#else
# define BFC_ASSERT(expr) ((void)(0))
#endif /* !NDEBUG */

/* Print a failed assertion diagnostic message and halt. */
void bfc_assert_fail(const char *file,
                     const char *fn, int line, const char *expr);

#endif /* !BFC_RTS_ASSERT_H */
