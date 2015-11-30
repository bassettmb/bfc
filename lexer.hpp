#ifndef BFC_LEXER_HPP
#define BFC_LEXER_HPP

#include "result.hpp"
#include "source.hpp"
#include "token.hpp"

namespace bfc {

template <class Source, class Traits = source_traits<Source>>
class lexer {

  using traits = Traits;

public:

  using source_type = typename traits::source_type;

  lexer(source_type source) : source(std::move(source)) {}

  result_type next(token &tok) noexcept {
    token::type kind;
    for (;;) {
      int ch = traits::next(source);
      advance(ch);
      tok.pos = pos;
      switch (ch) {
        case EOF:
          return traits::eof(source) ?
            result_type::DONE : result_type::FAIL;
        case '+':
          tok.kind = token::INC;
          return result_type::OK;
        case '-':
          tok.kind = token::DEC;
          return result_type::OK;
        case '<':
          tok.kind = token::MOVE_L;
          return result_type::OK;
        case '>':
          tok.kind = token::MOVE_R;
          return result_type::OK;
        case '[':
          tok.kind = token::LOOP_BEGIN;
          return result_type::OK;
        case ']':
          tok.kind = token::LOOP_END;
          return result_type::OK;
        case '.':
          tok.kind = token::PUT_CHAR;
          return result_type::OK;
        case ',':
          tok.kind = token::GET_CHAR;
          return result_type::OK;
        
#if defined(BFC_COMMENT_EXT) && BFC_COMMENT_EXT
        case '#': /* comment support (syntax extension) */
          for (;;) {
            ch = lexer.next();
            if (ch == EOF)
              return traits::eof(source) ?
                result_type::DONE : result_type::FAIL;
            advance(ch);
            if (ch == '\n')
              break;
          }
#endif

        default: /* unrecognized characters are ignored */
          break;
      }
    }
    tok.pos = pos;
    tok.kind = kind;
    return result_type::OK;
  }

private:

  void advance(int ch) noexcept
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