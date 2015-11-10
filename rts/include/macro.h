#ifndef BF_MACRO_H
#define BF_MACRO_H

#include "config.h"

/* Generic macros go here. */

/* two levels necessary because the preprocessor works from the outside in */
#define BF_STRINGIFY(s) #s
#define BF_TO_STRING(s) BF_STRINGIFY(s)

#define BF_SWAP(bind, fst, snd) \
  do { \
    (bind) = (fst); \
    (fst) = (snd); \
    (snd) = (bind); \
  } while (0)

/* attributes for warnings and other fun */

#ifdef BF_HAVE_TYPEOF
# define BF_MEMBER_CAST(type, member) \
    __typeof__ (((type *)0)->member)
#else
# define BF_MEMBER_CAST(type, member) const void
#endif /* typeof type-checking warnings */

#ifdef BF_HAVE_PURE
# define BF_PURE __attribute__((__pure__))
#else
# define BF_PURE /* nil */
#endif /* pure */

#ifdef BF_HAVE_UNUSED
# define BF_UNUSED __attribute__ ((__unused__))
#else
# define BF_UNUSED /* nil */
#endif /* unused */

#ifdef BF_HAVE_FORMAT
# define BF_PRINTF_FMT(FMT, ARGV) \
    __attribute__ ((format (printf, FMT, ARGV)))
#else
# define BF_PRINTF_FMT(FMT, ARGV) /* nil */
#endif /* format warnings */

#define BF_SIZEOF_ARRAY(arr) (sizeof (arr) / sizeof *(arr))

#define BF_CONT(elem, type, member) ((type *)((const char *) \
    (BF_MEMBER_CAST(type, member) *) { elem } - offsetof (type, member)))

#ifdef BF_HAVE_NORETURN
#  include <stdnoreturn.h>
#  define BF_NORETURN noreturn
#elif defined(BF_HAVE_GNU_NORETURN)
#  define BF_NORETURN __attribute__ ((__noreturn__))
#else
#  define BF_NORETURN /* nil */
#endif /* noreturn */

#endif /* !BF_MACRO_H */
