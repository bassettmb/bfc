#ifndef BF_CONFIG_H
#define BF_CONFIG_H

/* Abstraction layer for feature test macros. */

#define BF_REENTRANT_DEBUG

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
# define BF_UNIX
#endif

#if defined(__STDC_VERSION__)
#  if __STDC_VERSION__ >= 199901L
#    ifndef BF_HAVE_C99
#      define BF_HAVE_C99
#    endif
#  endif /* C99 */
#  if __STDC_VERSION__ >= 201112L
#    ifndef BF_HAVE_C11
#      define BF_HAVE_C11 
#    endif
#  endif /* C11 */
#endif /* STDC */

#ifdef BF_HAVE_C99
# ifndef BF_HAVE_BOOL
#   define BF_HAVE_BOOL
# endif
#endif /* C99 features */

#ifdef BF_HAVE_C11
# ifndef BF_HAVE_NORETURN
#   define BF_HAVE_NORETURN
# endif
#endif /* C11 features */

#if defined(__GNUC__)

# ifndef BF_HAVE_TYPEOF
#   define BF_HAVE_TYPEOF
# endif

/* attribute guards */

# ifndef BF_HAVE_PURE
#   define BF_HAVE_PURE
# endif

# ifndef BF_HAVE_GNU_NORETURN
#   define BF_HAVE_GNU_NORETURN
# endif

# ifndef BF_HAVE_FORMAT
#   define BF_HAVE_FORMAT
# endif

# ifndef BF_HAVE_UNUSED
#   define BF_HAVE_UNUSED
# endif

#endif /* GNUC extensions */

#endif /* !CONFIG_H */
