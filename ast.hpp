#ifndef BFC_AST_HPP
#define BFC_AST_HPP

#include "lexer.hpp"

namespace bfc {

class AstNode {

  public:

  private:
  
    bfc::position pos;
}

class AddNode : public AstNode {
    int value;
    int offset;
}

class MoveNode : public AstNode {
    
}

class LoopNode : public AstNode {
    
}

class ReadNode : public AstNode {
    
}

class WriteNode : public AstNode {
    
}

class MultiplyNode : public AstNode {
    
}

}

#endif /* !BFC_AST_HPP */
