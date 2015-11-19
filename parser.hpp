#ifndef BFC_PARSER_HPP
#define BFC_PARSER_HPP

#include "lexer.hpp"
#include "result.hpp"
#include "ast/ast.hpp"

namespace bfc {

template <class Lexer>
class parser {

    public:

        parser(Lexer lexer) : lexer(lexer) {}

        ast_program parse() {
            /* create result to hold lexer result */
            result_type res;
            /* create token to pass into lexer */
            token tok;

            for(;;) {
                res = lexer.next(tok);
                switch (res) {
                    case result_type::OK:
                        updateAst(tok);
                        break;
                    case result_type::DONE:
                        return ast;
                    case result_type::FAIL:
                    default:
                }
            }
        }

    private:

        Lexer lexer;

        /* sequece of instructions to return */
        ast_seq ast;

        /* stack to manage nested instructions in loop nodes */
        std::stack<std::vector<std::unique_ptr<AstNode>>> stack;

        void updateAst(token &tok) {
            token::type kind = tok.kind;
            position pos = tok.pos;
            std::unique_ptr<AstNode> node;

            switch (tok.kind) {
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
