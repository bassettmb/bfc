#ifndef BFC_PARSER_HPP
#define BFC_PARSER_HPP

#include "lexer.hpp
#include "ast.hpp"

namespace bfc {
    
template <class Lexer>
class Parser {
    
    using result = typename Lexer::result;
    
    public:
    
        Parser(Lexer lexer) : this.lexer(lexer) {}
    
        std:vector<AstNode> parse() {
            /* create result to hold lexer result */
            result res = OK;
            /* create token to pass into lexer */
            token tok;
            
            for(;;) {
                res = lexer.next(tok);
                switch (res) {
                    case OK:
                        updateAst(tok);
                        break;
                    case DONE:
                        return ast;
                    case FAIL:
                        
                    default:
                }
            }
        }
        
    private:
    
        Lexer lexer;
        
        /* vector of instructions to return */
        std::vector<std::unique_ptr<AstNode>> ast;
        
        void updateAst(token &tok) {
            token::type kind = tok.kind;
            position pos = tok.pos;
            std::unique_ptr<AstNode> node;
            
            switch (kind) {
                case INC:
                    node = std::make_unique<AddNode>(pos, 1);
                    ast.push_back(node);
                    break;
                case DEC:
                    node = std::make_unique<AddNode>(pos, -1);
                    ast.push_back(node);
                    break;
                case MOVE_R:
                    node = std::make_unique<MoveNode>(pos, 1);
                    ast.push_back(node);
                    break;
                case MOVE_L:
                    node = std::make_unique<MoveNode>(pos, -1);
                    ast.push_back(node);
                    break;
                case LOOP_BEGIN:
                case LOOP_END:
                case PUT_CHAR:
                    node = std::make_unique<WriteNode>(pos);
                    ast.push_back(node);
                    break;
                case GET_CHAR:
                    node = std::make_unique<ReadNode>(pos);
                    ast.push_back(node);
                    break;
                default:
                
            }
        }

};

}

#endif /* !BFC_PARSER_HPP */
