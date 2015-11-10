#include "str.h"

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERRBUFLEN 256 /* base buffer size for strerror_r buffer */

void *
bf_memdup(const void *ptr, size_t nbytes)
{
  void *mem;

  mem = malloc(nbytes);
  if (!mem)
    return 0;

  return memcpy(mem, ptr, nbytes);
}

char *
bf_strdup(const char *str)
{
  size_t size;

  size = strlen(str);
  return bf_memdup(str, size + 1);
}

char *
bf_strndup(const char *str, size_t size)
{
  char *res;
  size_t ix, nbytes;

  size = strnlen(str, size);
  nbytes = size + 1;
  res = malloc(nbytes);

  if (!res)
    return 0;

  memcpy(res, str, size);
  res[size] = '\0';
  return res;
}

char *
bf_basename(const char *path)
{
  size_t size;
  const char *off;

  size = strlen(path);
  off = path + size;

  while (off --> path) {
    if (off[0] == '/') {
      if (off == path || off[-1] != '\\')
        return (char *)(off + 1);
      else
        /* we can skip the next character because it's an escape */
        --off;
    }
  }

  return (char *)off;
}

size_t
bf_dirlen(const char *path)
{
  char *base;
  size_t size;

  base = bf_basename(path);
  size = path - base;

  /* chop off the leading forward slash */

  if (size == 1)
    size = 0;
  else if (size > 1)
    size -= 2;

  return size;
}

int
bf_vfmtlen(const char *fmt, va_list argv)
{
  int res;
  va_list argv_dup;

  va_copy(argv_dup, argv);
  res = vsnprintf(0, 0, fmt, argv_dup);
  va_end(argv_dup);
  return res >= 0 ? res : 0;
}

int
bf_fmtlen(const char *fmt, ...)
{
  int res;
  va_list argv;

  va_start(argv, fmt);
  res = bf_vfmtlen(fmt, argv);
  va_end(argv);

  return res;
}

size_t
bf_errlen(int errnum)
{
  int res;
  size_t len;

  len = ERRBUFLEN;
  for (;;) {
    char buf[len];
    if (!strerror_r(errnum, buf, len)) {
      len = strlen(buf);
      break;
    }
    len *= 2;
  }

  return len;
}
