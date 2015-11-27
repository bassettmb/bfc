#ifndef BFC_AST_VISITOR_HPP
#define BFC_AST_VISITOR_HPP

#include <memory>

namespace bfc {
namespace ast {

class program;
class add;
class sub;
class mul;
class mov;
class read;
class write;
class loop;

class visitor {

public:

  enum status {
    BREAK = 0,
    CONTINUE
  };

  virtual ~visitor(void) = default;

  virtual status visit(program &node) { return CONTINUE; }
  virtual status visit(const program &node) { return CONTINUE; }
  virtual status visit(add &node) { return CONTINUE; }
  virtual status visit(const add &node) { return CONTINUE; }
  virtual status visit(sub &node) { return CONTINUE; }
  virtual status visit(const sub &node) { return CONTINUE; }
  virtual status visit(mov &node) { return CONTINUE; }
  virtual status visit(const mov &node) { return CONTINUE; }
  virtual status visit(mul &node) { return CONTINUE; }
  virtual status visit(const mul &node) { return CONTINUE; }
  virtual status visit(loop &node) { return CONTINUE; }
  virtual status visit(const loop &node) { return CONTINUE; }
  virtual status visit(read &node) { return CONTINUE; }
  virtual status visit(const read &node) { return CONTINUE; }
  virtual status visit(write &node) { return CONTINUE; }
  virtual status visit(const write &node) { return CONTINUE; }

};

}
}

#endif /* !BFC_AST_VISITOR_HPP */
