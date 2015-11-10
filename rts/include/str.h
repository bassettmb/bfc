#ifndef STR_H
#define STR_H

#include <stdarg.h>
#include <stddef.h>

void *bf_memdup(const void *ptr, size_t nbytes);
char *bf_strdup(const char *str);
char *bf_strndup(const char *str, size_t size);
char *bf_basename(const char *path);
size_t bf_dirlen(const char *path);

int bf_vfmtlen(const char *fmt, va_list argv);
int bf_fmtlen(const char *fmt, ...);
size_t bf_errlen(int errnum);

#endif /* !STR_H */
