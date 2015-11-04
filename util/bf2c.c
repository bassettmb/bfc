#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

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
bf_indent(FILE *out, int level)
{
  while (level--) {
    putc(' ', out);
    putc(' ', out);
  }
}

void
bf_pp(FILE *out, int level, const char *text)
{
  bf_indent(out, level);
  fputs(text, out);
  putc('\n', out);
}

void
bf_compile(FILE *out, const char *text)
{
  bf_pp(out, 0, "#include <stdio.h>");
  bf_pp(out, 0, "#include <stdint.h>");
  bf_pp(out, 0, "static uint8_t heap[65536];");
  bf_pp(out, 0, "static uint8_t *mem = heap;");
  bf_pp(out, 0, "\n");
  bf_pp(out, 0, "int");
  bf_pp(out, 0, "main(void)");
  bf_pp(out, 0, "{");

  int level = 1;

  for (;;) {
    switch (*text++) {
      case '\0': goto exit;
      case '>': bf_pp(out, level, "mem += 1;"); break;
      case '<': bf_pp(out, level, "mem -= 1;"); break;
      case '+': bf_pp(out, level, "*mem += 1;"); break;
      case '-': bf_pp(out, level, "*mem -= 1;"); break;
      case '.': bf_pp(out, level, "putchar(*mem);"); break;
      case ',': bf_pp(out, level, "*mem = getchar();"); break;
      case '[': bf_pp(out, level, "while(*mem) {"); level += 1; break;
      case ']': level -= 1; bf_pp(out, level, "}"); break;
      /* ignore unrecognized characters */
      default: break;
    }
  }

exit:
  bf_pp(out, level, "return 0;");
  bf_pp(out, 0, "}");
}

int
main(int argc, char **argv)
{
  if (argc != 2) {
    puts("usage: bf2c <bf-file>");
    exit(EXIT_FAILURE);
  }

  char *text = bf_read(argv[1]);
  if (!text) {
    perror("bf2c");
    exit(EXIT_FAILURE);
  }

  bf_compile(stdout, text);
  return 0;
}
