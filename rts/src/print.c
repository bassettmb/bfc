#include "str.h"
#include "print.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define ERRBUFLEN 1024

/* Re-entrant printf routines. */

static ssize_t bf_do_write(int fd, const void *ptr, size_t bytes);

ssize_t
bf_do_write(int fd, const void *ptr, size_t bytes)
{
  const char *mem;
  size_t rem, total;
  ssize_t nwritten;

  mem = ptr;
  rem = bytes;

  /* Since presumably this is being called from a signal-laden program, we
   * want to ensure that we handle EINTR in case no-restart handlers have
   * been installed.
   */

  do {
    nwritten = write(fd, mem, rem);
    if (nwritten >= 0) {
      rem -= nwritten;
      if (!rem)
        break;
      mem += nwritten;
    } else if (errno != EINTR) {
      bytes -= rem;
      break;
    }
  } while (rem);


  return bytes ? bytes : -1;
}

int
bf_vfdprintf_r(int fd, const char *fmt, va_list argv)
{
  int res, rval;

  res = bf_vfmtlen(fmt, argv);
  
  if (res < 0) {
    rval = -1;
  } else {
    va_list argv_dup;
    /* add one for null terminator */
    size_t len = res + 1;
    char buffer[len];

    va_copy(argv_dup, argv);
    res = vsnprintf(buffer, len, fmt, argv_dup);
    rval = res >= 0 && res < len ? (int)bf_do_write(fd, buffer, len) : -1;
    va_end(argv_dup);
  }

  return rval;
}

int
bf_fdputsn_r(int fd, const char *str, size_t len)
{
  int res;

  if (str) {
    ssize_t nwritten;

    nwritten = bf_do_write(fd, str, len);
    res = nwritten == len ? nwritten : EOF;
  } else {
    errno = EFAULT; /* bad address! */
    res = EOF;
  }

  return res;
}

int
bf_fdputs_r(int fd, const char *str)
{
  int res;

  if (str) {
    res = bf_fdputsn_r(fd, str, strlen(str));
  } else {
    errno = EFAULT;
    res = EOF;
  }

  return res;
}

int
bf_fdputsln_r(int fd, const char *str)
{
  int res;

  if (str) {
    size_t len, nbytes;
    ssize_t nwritten;

    len = strlen(str);
    nbytes = len + 1;

    char buffer[nbytes];

    memcpy(buffer, str, len);
    buffer[len] = '\n';
    res = bf_fdputsn_r(fd, str, nbytes);
  } else {
    errno = EFAULT;
    res = EOF;
  }

  return res;
}

int
bf_fdprintf_r(int fd, const char *fmt, ...)
{
  int res;
  va_list argv;

  va_start(argv, fmt);
  res = bf_vfdprintf_r(fd, fmt, argv);
  va_end(argv);

  return res;
}

int
bf_putsn_r(const char *str, size_t len)
{
  return bf_fdputsn_r(STDOUT_FILENO, str, len);
}

int
bf_eputsn_r(const char *str, size_t len)
{
  return bf_fdputsn_r(STDERR_FILENO, str, len);
}

int
bf_puts_r(const char *str)
{
  return bf_fdputs_r(STDOUT_FILENO, str);
}

int
bf_eputs_r(const char *str)
{
  return bf_fdputs_r(STDERR_FILENO, str);
}

int
bf_putsln_r(const char *str)
{
  return bf_fdputsln_r(STDOUT_FILENO, str);
}

int
bf_eputsln_r(const char *str)
{
  return bf_fdputsln_r(STDERR_FILENO, str);
}

int
bf_printf_r(const char *fmt, ...)
{
  int res;
  va_list argv;

  va_start(argv, fmt);
  res = bf_vfdprintf_r(STDOUT_FILENO, fmt, argv);
  va_end(argv);

  return res;
}

int
bf_eprintf_r(const char *fmt, ...)
{
  int res;
  va_list argv;

  va_start(argv, fmt);
  res = bf_vfdprintf_r(STDERR_FILENO, fmt, argv);
  va_end(argv);

  return res;
}
