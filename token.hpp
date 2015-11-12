#ifndef BFC_TOKEN_HPP
#define BFC_TOKEN_HPP

namespace bfc {

struct position {
  unsigned long pos;
  unsigned long row;
  unsigned long col;
};

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
  position pos;

};

}

#endif /* !BFC_TOKEN_HPP */
