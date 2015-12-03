#include <cstdio>
#include <cstring>
#include <fstream>

static const char PROGNAME[] = "bfc";
static const char FILETYPE[] = "bf";
static const size_t FILETYPE_LEN = 2;
// TODO: add version number (requires configure setup)

using namespace bfc;

static void
print_usage(FILE *out)
{
  fprintf(out, "usage: %s <source-file>", PROGNAME);
}

static void
print_filename_error(FILE *out)
{
  fprintf(out, "file must be of type %s", FILETYPE);
}

static int
handle_filepath(const char *filepath)
{
  size_t len = strlen(filepath);
  if (filepath[len - FILETYPE_LEN - 1] != '.'){
    print_filename_error(stderr);
    return -1;
  }
  for (size_t i = FILETYPE_LEN ; i > 0; --i){
    if (filepath[len - i] != FILETYPE[FILETYPE_LEN - i]){
      print_filename_error(stderr);
      return -1;
    }
  }

  std::fstream * stream = new std::fstream(filepath);
  stream_source streamSource(stream);
  lexer<stream_source> lexer(streamSource);
  parser<stream_source> parser(lexer);
  ast_program ast = parser.parse();

  return 0;
}

int
main(int argc, const char *const *argv)
{
  if (argc != 2) {
    print_usage(stderr);
    exit(EXIT_FAILURE);
  }

  handle_filepath(argv[1]);

  return 0;
}
