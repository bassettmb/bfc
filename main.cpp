#include <cstdio>
#include <cstring>

static const char PROGNAME[] = "bfc";
// TODO: add version number (requires configure setup)

static void
print_usage(FILE *out)
{
  fprintf(out, "usage: %s <source-file> [<source-file>]", PROGNAME);
}

static int 
handle_filepath(const char *filepath);

int
main(int argc, const char *const *argv)
{
  if (argc < 2) {
    print_usage(stderr);
    exit(EXIT_FAILURE);
  }

  for (const char *off = argv; *off; off += 1) {

    int ch;
    const char *arg = off;

    ch = arg[0];
    if (ch != '-')
      continue;

    /* handle -h */
    ch = arg[1];
    if (ch == 'h') {
      print_usage(stdout);
      exit(EXIT_SUCCESS);
    }

    /* handle --help*/
    if (ch == '-' && !strcmp(arg + 2, "help")) {
      print_usage(stdout);
      exit(EXIT_SUCCESS);
    }

  }

  for (const char *off = argv; *off; off += 1)
    handle_filepath(off);

  return 0;
}
