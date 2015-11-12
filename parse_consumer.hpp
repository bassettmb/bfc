#ifndef BFC_PARSE_CONSUMER_HPP
#define BFC_PARSE_CONSUMER_HPP

#include "token.hpp"

namespace bfc {

class parse_consumer {
public:
  virtual ~parse_consumer(void) = default;
  virtual void on_add(token tok) = 0;
  virtual void on_sub(token tok) = 0;
  virtual void on_move_left(token tok) = 0;
  virtual void on_move_right(token tok) = 0;
  virtual void on_loop_begin(token tok) = 0;
  virtual void on_loop_end(token tok) = 0;
  virtual void on_get_char(token tok) = 0;
  virtual void on_put_char(token tok) = 0;
};

}

#endif  /* !BFC_PARSE_CONSUMER_HPP */
