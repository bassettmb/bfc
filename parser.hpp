#ifndef BFC_PARSER_HPP
#define BFC_PARSER_HPP

#include "lexer.hpp"
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

        /* stack to manage nested instructions in loop nodes */
        std::stack<std::vector<std::unique_ptr<AstNode>>> stack;

        void updateAst(token &tok) {
            token::type kind = tok.kind;
            position pos = tok.pos;
            std::unique_ptr<AstNode> node;

            switch (kind) {
                case token::INC:
                    node = std::make_unique<AddNode>(pos, 1);
                    ast.push_back(node);
                    break;
                case token::DEC:
                    node = std::make_unique<AddNode>(pos, -1);
                    ast.push_back(node);
                    break;
                case token::MOVE_R:
                    node = std::make_unique<MoveNode>(pos, 1);
                    ast.push_back(node);
                    break;
                case token::MOVE_L:
                    node = std::make_unique<MoveNode>(pos, -1);
                    ast.push_back(node);
                    break;
                case token::LOOP_BEGIN:
                    stack.push(ast);
                    ast = std::vector<std::unique_ptr<AstNode>>();
                    break;
                case token::LOOP_END:
                    if (!stack.empty()) {
                        node = std::make_unique<LoopNode>(pos, ast);
                        ast = stack.top();
                        stack.pop();
                        ast.push_back(node);
                    } else {
                        // throw exception
                    }
                    break;
                case token::PUT_CHAR:
                    node = std::make_unique<WriteNode>(pos);
                    ast.push_back(node);
                    break;
                case token::GET_CHAR:
                    node = std::make_unique<ReadNode>(pos);
                    ast.push_back(node);
                    break;
                default:

            }
        }

};

}

#endif /* !BFC_PARSER_HPP */
