#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <stdexcept>
#include "source.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "pprint/c_pprint.hpp"
#include "optimizer.hpp"

static const char PROGNAME[] = "bfc";
static const char FILETYPE[] = "bf";
static const size_t FILETYPE_LEN = 2;
// TODO: add version number (requires configure setup)

using namespace bfc;

static void
print_usage(FILE *out)
{
  fprintf(out, "usage: %s <source-file>\n", PROGNAME);
}

static void
print_filename_error(FILE *out)
{
  fprintf(out, "file must be of type %s\n", FILETYPE);
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

  parser<stream_source> parser{
    lexer<stream_source>{stream_source{new std::fstream{filepath}}}};
  optimizer optimizer{false, true};
  try
  {
    ast_node ast = optimizer.optimize(parser.parse());
  }
  catch (std::runtime_error& e)
  {
    printf("%s", e.what());
    return -2;
  }
  pprint::c_pprint printer{};
  std::ofstream output{std::string{filepath} + ".c"};
  printer.emit(output, astNode);


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
