#ifndef BFC_AST_HPP
#define BFC_AST_HPP

#include "ast/ast_base.hpp"
#include "token.hpp"

namespace bfc {

class AstNode : public ast_base {
  private:
    position pos;
};

class AddNode : public AstNode {
  public:
    int value;
    int offset;
    AddNode(int value, int offset) : value(value), offset(offset) {}
};

class MoveNode : public AstNode {
  public:
    int offset;
    MoveNode(int offset) : offset(offset) {}
};

class LoopNode : public AstNode {
  public:
    std::vector<std::unique_ptr<AstNode>> ast;
    LoopNode(std::vector<std::unique_ptr<AstNode>> ast) : ast(ast) {}
};

class ReadNode : public AstNode {};

class WriteNode : public AstNode {};

class MultiplyNode : public AstNode {
  public:
    int value;
    int offset;
    MultiplyNode(int value, int offset) : value(value), offset(offset) {}
};

}

#endif /* !BFC_AST_HPP */
