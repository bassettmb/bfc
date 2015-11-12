#ifndef BFC_DERPY_CODEGEN_HPP
#define BFC_DERPY_CODEGEN_HPP

#include <iostream>
#include "token.hpp"
#include "parse_consumer.hpp"

namespace bfc {

class derpy_c_codegen : public parse_consumer {

public:

  derpy_c_codegen(void)
  {
    std::cout
      << "#include <stdint.h>" << std::endl
      << "#include <stdio.h>" << std::endl
      << std::endl
      << "static uint8_t heap[65536];" << std::endl
      << "static uint8_t *mem = heap + 8192;" << std::endl
      << std::endl
      << "int main(void)" << std::endl
      << "{" << std::endl;
  }
      

  void on_add(token tok)
  {
    std::cout << "*mem += 1;" << std::endl;
  }

  void on_sub(token tok)
  {
    std::cout << "*mem -= 1;" << std::endl;
  }

  void on_move_left(token tok)
  {
    std::cout << "mem -= 1;" << std::endl;
  }

  void on_move_right(token tok)
  {
    std::cout << "mem += 1;" << std::endl;
  }

  void on_loop_begin(token tok)
  {
    std::cout << "while (*mem) {" << std::endl;
  }

  void on_loop_end(token tok)
  {
    std::cout << "}" << std::endl;
  }

  void on_put_char(token tok)
  {
    std::cout << "putchar(*mem);" << std::endl;
  }

  void on_get_char(token tok)
  {
    std::cout << "*mem = getchar();" << std::endl;
  }

};

}

#endif  /* !BFC_DERPY_CODEGEN_HPP */
