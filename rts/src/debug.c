#include "debug.h"
#include "str.h"
#include "print.h"

#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int bf_write_error(const char *str, size_t len);
static BF_NORETURN void bf_debug_halt(void);
static void bf_debug_eprint(int err);
static void bf_debug_vprint(
    const char *file, const char *fn, int lineno, int err,
    const char *fmt, va_list argv);

int
bf_write_error(const char *str, size_t len)
{
  size_t res;
  res = fwrite(str, sizeof *str, len, stderr);
  return res ? 0 : -1;
}

void
bf_debug_halt(void)
{
  for (;;) {
    abort();
    exit(EXIT_FAILURE);
  }
}

static void
bf_debug_vprint(
    const char *file, const char *fn, int lineno,
    int err, const char *fmt, va_list argv)
{
  int res;

  size_t llen = bf_fmtlen("%s:%d:%s", file, lineno, fn);
  size_t elen = err ? bf_errlen(err) : 0;
  size_t flen = fmt ? bf_vfmtlen(fmt, argv) : 0;
  size_t nbytes = llen + 2 + flen + 2 + elen + 1;

  char *off;
  char buffer[nbytes];

  memset(buffer, 0, nbytes);
  off = buffer;
  snprintf(off, llen + 1, "%s:%d:%s", file, lineno, fn);
  off += llen;

  if (fmt) {
    va_list argv_dup;
    *off++ = ':';
    *off++ = ' ';
    va_copy(argv_dup, argv);
    vsnprintf(off, flen + 1, fmt, argv_dup);
    va_end(argv_dup);
    off += flen;
  }

  if (err) {
    *off++ = ':';
    *off++ = ' ';
    strerror_r(err, off, elen + 1);
    off += elen;
  }

  *off++ = '\n';
  bf_eputsn_r(buffer, nbytes);
}

void
bf_debug_warn(
    const char *file, const char *fn, int lineno, const char *fmt, ...)
{
  int errno_sav;
  va_list argv;

  errno_sav = errno;
  va_start(argv, fmt);
  bf_debug_vprint(file, fn, lineno, 0, fmt, argv);
  va_end(argv);
  errno = errno_sav;
}

void
bf_debug_warn_error(const char *file, const char *fn, int lineno,
         const char *fmt, ...)
{
  int errno_sav;
  va_list argv;

  errno_sav = errno;
  va_start(argv, fmt);
  bf_debug_vprint(file, fn, lineno, errno_sav, fmt, argv);
  va_end(argv);
  errno = errno_sav;
}

void
bf_debug_panic(
    const char *file, const char *fn, int lineno, const char *fmt, ...)
{
  va_list argv;

  va_start(argv, fmt);
  bf_debug_vprint(file, fn, lineno, 0, fmt, argv);
  bf_debug_halt();
  va_end(argv);
}

void
bf_debug_panic_error(
    const char *file, const char *fn, int lineno, const char *fmt, ...)
{
  va_list argv;

  va_start(argv, fmt);
  bf_debug_vprint(file, fn, lineno, errno, fmt, argv);
  bf_debug_halt();
  va_end(argv);
}
