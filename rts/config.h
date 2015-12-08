#ifndef BFC_RTS_CONFIG_H
#define BFC_RTS_CONFIG_H

#define BFC_RTS_NAME "bfc_rts"

#if defined(BFC_RTS_GCC) || defined(BFC_RTS_CLANG)
# ifdef BFC_RTS_WIN
#   define BFC_RTS_EXPORT __attribute__((dllexport))
# else /* !BFC_RTS_WIN */
#   define BFC_RTS_EXPORT __attribute__((visibility("default")))
# endif
#elif defined(BFC_RTS_MSVC)
# define BFC_RTS_EXPORT __declspec(dllexport)
#else
# define BFC_RTS_EXPORT /* nothing */
#endif

#endif /* !BFC_RTS_CONFIG_H */
