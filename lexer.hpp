#ifndef BFC_LEXER_HPP
#define BFC_LEXER_HPP

#include "source.hpp"
#include "token.hpp"

namespace bfc {

template <class Source, class Traits = source_traits<Source>>
class lexer {

  using traits = Traits;

public:

  enum result {
    FAIL = -1,
    OK = 0,
    DONE = 1
  };

  using source_type = typename traits::source_type;

  lexer(source_type source) : source(std::move(source)) {}

  result next(token &tok) noexcept {
    token::type kind;
    for (;;) {
      int ch = traits::next(source);
      advance(ch);
      switch (ch) {
        case EOF: return source.eof() ? DONE : FAIL;
        case '+': kind = token::INC; break;
        case '-': kind = token::DEC; break;
        case '<': kind = token::MOVE_L; break;
        case '>': kind = token::MOVE_R; break;
        case '[': kind = token::LOOP_BEGIN; break;
        case ']': kind = token::LOOP_END; break;
        case '.': kind = token::PUT_CHAR; break;
        case ',': kind = token::GET_CHAR; break;
        /* unrecognized characters are comments */
        default: continue;
      }
      break;
    }
    tok.pos = pos;
    tok.kind = kind;
    return OK;
  }

private:

  void advance(int ch)
  {
    pos.pos += 1;
    if (ch == '\n') {
      pos.col = 0;
      pos.row += 1;
    } else {
      pos.col += 1;
    }
  }

  position pos;
  source_type source;

};

}

#endif /* !BFC_LEXER_HPP */
