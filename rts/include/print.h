#ifndef BF_PRINT_H
#define BF_PRINT_H

#include <stdarg.h>
#include <stddef.h>

/* probe for error message length */

size_t bf_errlen(int errnum);

/* reentrant printing routines */

int bf_vfdprintf_r(int fd, const char *fmt, va_list argv);
int bf_fdputsn_r(int fd, const char *str, size_t len);
int bf_fdputs_r(int fd, const char *str);
int bf_fdputsln_r(int fd, const char *str);
int bf_fdprintf_r(int fd, const char *fmt, ...);

int bf_putsn_r(const char *str, size_t len);
int bf_eputsn_r(const char *str, size_t len);
int bf_puts_r(const char *str);
int bf_eputs_r(const char *str);
int bf_putsln_r(const char *str);
int bf_eputsln_r(const char *str);
int bf_printf_r(const char *fmt, ...);
int bf_eprintf_r(const char *fmt, ...);

#endif /* !BF_PRINT_H */
