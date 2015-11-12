#ifndef BFC_AST_VISITOR_HPP
#define BFC_AST_VISITOR_HPP

#include <memory>

namespace bfc {

class ast_program;
class ast_add;
class ast_mul;
class ast_mov;
class ast_read;
class ast_write;
class ast_loop;

class ast_visitor {

public:

  enum status {
    BREAK = 0,
    CONTINUE
  };

  virtual ~ast_visitor(void) = default;

  virtual status visit(const ast_add &node) { return CONTINUE; }
  virtual status visit(ast_mov &node) { return CONTINUE; }
  virtual status visit(const ast_mov &node) { return CONTINUE; }
  virtual status visit(ast_read &node) { return CONTINUE; }
  virtual status visit(const ast_read &node) { return CONTINUE; }
  virtual status visit(ast_loop &node) { return CONTINUE; }
  virtual status visit(const ast_loop &node) { return CONTINUE; }
  virtual status visit(ast_write &node) { return CONTINUE; }
  virtual status visit(const ast_write &node) { return CONTINUE; }

};


}

#endif /* !BFC_AST_VISITOR_HPP */
