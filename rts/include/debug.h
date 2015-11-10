#ifndef BF_DEBUG_H
#define BF_DEBUG_H

#include "macro.h"

/* fatal */

BF_NORETURN void bf_debug_panic(
    const char *file, const char *fn, int lineno,
    const char *fmt, ...) BF_PRINTF_FMT(4, 5);

BF_NORETURN void bf_debug_panic_error(
    const char *file, const char *fn, int lineno,
    const char *fmt, ...) BF_PRINTF_FMT(4, 5);

#define BF_PANIC(...) \
  bf_debug_panic(__FILE__, __func__, __LINE__, __VA_ARGS__)
#define BF_PANIC_ERROR(...) \
  bf_debug_panic_error(__FILE__, __func__, __LINE__, __VA_ARGS__)

/* non-fatal, preserve errno */

void bf_debug_warn(
    const char *file, const char *fn, int lineno,
    const char *fmt, ...) BF_PRINTF_FMT(4, 5);

void bf_debug_warn_error(
    const char *file, const char *fn, int lineno,
    const char *fmt, ...) BF_PRINTF_FMT(4, 5);

#define BF_WARN(...) \
  bf_debug_warn(__FILE__, __func__, __LINE__, __VA_ARGS__)
#define BF_WARN_ERROR(...) \
  bf_debug_warn_error(__FILE__, __func__, __LINE__, __VA_ARGS__)

#define BF_LOG(...) BF_WARN(__VA_ARGS__)

#endif /* !BF_DEBUG_H */

#undef BF_ASSERT
#undef BF_ASSERT_ERROR
#undef BF_EXPECT
#undef BF_EXPECT_ERROR
#undef BF_IMPOSSIBLE

#ifndef NDEBUG
# define BF_ASSERT(expr) \
    ((void)((expr) ? 0 : \
      BF_PANIC("assertion `%s' failed", BF_TO_STRING(expr))))
# define BF_ASSERT_ERROR(expr) \
    ((void)((expr) ? 0 : \
      BF_PANIC_ERROR("assertion `%s' failed", BF_TO_STRING(expr))))
# define BF_EXPECT(expr) \
    ((void)((expr) ? 0 : \
      BF_WARN("expectation `%s' did not hold", BF_TO_STRING(expr))))
# define BF_EXPECT_ERROR(expr) \
    ((void)((expr) ? 0 : \
      BF_WARN_ERROR("expectation `%s' did not hold", BF_TO_STRING(expr))))
# define BF_IMPOSSIBLE() BF_PANIC("the impossible happened")
#else
# define BF_ASSERT(expr) ((void)0)
# define BF_ASSERT_ERROR(expr) ((void)0)
# define BF_EXPECT(expr) ((void)0)
# define BF_EXPECT_ERROR(expr) ((void)0)
# define BF_IMPOSSIBLE() ((void)0)
#endif /* !NDEBUG */

