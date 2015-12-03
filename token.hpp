#ifndef BFC_TOKEN_HPP
#define BFC_TOKEN_HPP

#include "source_loc.hpp"

namespace bfc {

struct token {

  enum type {
    INC,
    DEC,
    MOVE_L,
    MOVE_R,
    LOOP_BEGIN,
    LOOP_END,
    PUT_CHAR,
    GET_CHAR
  };

  type kind;
  source_loc loc;

};

}

#endif /* !BFC_TOKEN_HPP */
