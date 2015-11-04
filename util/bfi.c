#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* constants are arbitrary */
#define HEAPSIZE 65536

static const char progname[] = "bfi";

static FILE *bf_stdin;
static FILE *bf_stdout;

static uint8_t heap[HEAPSIZE];
static uint8_t *hp = heap;

static char *progtext;
static const char *pc;

static void
bf_syserror(void)
{
  perror(progname);
  abort();
}

static void
bf_error(const char *msg)
{
  fflush(stdout);
  fprintf(stderr, "%s: %td: %s\n", progname, pc - progtext, msg);
  abort();
}

static inline void
bf_next(void)
{
  if (hp - heap >= HEAPSIZE)
    bf_error("out of memory");
  hp += 1;
}

static inline void
bf_prev(void)
{
  if (hp == heap)
    bf_error("out of memory");
  hp -= 1;
}

static inline void
bf_inc(void)
{
  *hp += 1;
}

static inline void
bf_dec(void)
{
  *hp -= 1;
}

static inline void
bf_putc(void)
{
  putc(*hp, bf_stdout);
  fflush(bf_stdout);
}

static inline void
bf_getc(void)
{
  int ch = getc(bf_stdin);
  /*
  if (ch == EOF)
    bf_syserror();
    */
  if (ch != EOF)
    *hp = ch;
}

static inline void
bf_jmp_fwd(void)
{
  if (*hp)
    return;

  int level = 0;
  for (;;) {
    switch (*pc++) {
      case '\0':
        bf_error("unmatched '['");
      case '[': 
        level += 1;
        break;
      case ']':
        if (!level)
          return;
        level -= 1;
        break;
      default:
        /* ignore everything else */
        break;
    }
  }
}

static inline void
bf_jmp_bwd(void)
{
  if (!*hp)
    return;

  int level = 0;
  pc -= 1; /* undo the automatic increment from bf_eval */
  for (;; pc -= 1) {
    if (pc == progtext)
      bf_error("unmatched ']'");
    switch (pc[-1]) {
      case '[': 
        if (!level)
          return;
        level -= 1;
        break;
      case ']':
        level += 1;
        break;
      default:
        /* ignore everything else */
        break;
    }
  }
}

char *
bf_read(const char *filepath)
{
  FILE *input = fopen(filepath, "r");
  if (!input)
    return 0;

  /* calculate file size in bytes */
  long begin = ftell(input);
  if (begin < 0)
    goto file_fail;
  if (fseek(input, 0, SEEK_END))
    goto file_fail;
  long end = ftell(input);
  if (end < 0)
    goto file_fail;

  /* remember to seek back to beginning! */
  if (fseek(input, 0, SEEK_SET))
    goto file_fail;

  assert(begin <= end);
  size_t navail = end - begin;
  size_t buflen = navail + 1;

  char *buf = malloc(buflen);
  if (!buf)
    goto file_fail;

  size_t nread = fread(buf, sizeof *buf, buflen, input);
  if (nread < navail) {
    if (ferror(input))
      goto read_fail;
    /* something odd happened ... but we can work with it */
    buf[nread] = '\0';
    char *tmp = realloc(buf, nread);
    if (!tmp)
      goto read_fail;
    buf = tmp;
  }

  fclose(input);
  return buf;

read_fail:
  free(buf);
file_fail:
  fclose(input);
  return 0;
}

void
bf_cleanup(void)
{
  if (progtext) {
    free(progtext);
    progtext = 0;
  }
  if (bf_stdin != stdin) {
    fclose(bf_stdin);
    bf_stdin = stdin;
  }
  if (bf_stdout != stdout) {
    fclose(bf_stdout);
    bf_stdout = stdout;
  }
}

void
bf_init(char *program, FILE *in, FILE *out)
{
  progtext = program;
  memset(heap, 0, sizeof heap);
  bf_stdin = in ? in : stdin;
  bf_stdout = out ? out : stdout;
  hp = heap;
  pc = progtext;
}

void
bf_eval(void)
{
  for (;;) {
    switch (*pc++) {

      case '\0': return;

      case '>': bf_next(); break;
      case '<': bf_prev(); break;

      case '+': bf_inc(); break;
      case '-': bf_dec(); break;

      case '.': bf_putc(); break;
      case ',': bf_getc(); break;

      case '[': bf_jmp_fwd(); break;
      case ']': bf_jmp_bwd(); break;

      /* ignore unrecognized characters */
      default: break;
    }
  }
}

int
main(int argc, char **argv)
{
  if (argc != 2) {
    printf("usage: %s <bf-file>\n", progname);
    exit(EXIT_FAILURE);
  }

  char *text = bf_read(argv[1]);
  if (!text)
    bf_syserror();
  bf_init(text, 0, 0);
  bf_eval();
  return 0;
}
