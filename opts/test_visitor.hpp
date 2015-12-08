#ifndef BFC_TEST_VISITOR_HPP
#define BFC_TEST_VISITOR_HPP

#include "ast/visitor.hpp"
#include "ast/mod.hpp"

namespace bfc {
namespace ast {

class test_visitor : public visitor {

public:

  virtual status visit(program &node) { return BREAK; }
  virtual status visit(const program &node) { return BREAK; }
  virtual status visit(set &node) { return BREAK; }
  virtual status visit(const set &node) { return BREAK; }
  virtual status visit(add &node) { return BREAK; }
  virtual status visit(const add &node) { return BREAK; }
  virtual status visit(sub &node) { return BREAK; }
  virtual status visit(const sub &node) { return BREAK; }
  virtual status visit(mov &node) { return BREAK; }
  virtual status visit(const mov &node) { return BREAK; }
  virtual status visit(mul &node) { return BREAK; }
  virtual status visit(const mul &node) { return BREAK; }
  virtual status visit(loop &node) { return BREAK; }
  virtual status visit(const loop &node) { return BREAK; }
  virtual status visit(read &node) { return BREAK; }
  virtual status visit(const read &node) { return BREAK; }
  virtual status visit(write &node) { return BREAK; }
  virtual status visit(const write &node) { return BREAK; }

};

}
}

#endif /* !BFC_TEST_VISITOR_HPP */
