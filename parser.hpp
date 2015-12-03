#ifndef BFC_PARSER_HPP
#define BFC_PARSER_HPP

#include "lexer.hpp"
#include "result.hpp"
#include "ast.hpp"

namespace bfc {

template <class Source, class Traits = source_traits<Source>>
class parser {

    public:

        using Lexer = lexer<Source, Traits>;

        parser(Lexer lexer) : lexer(std::move(lexer)) {}

        ast_node parse() {
            /* create result to hold lexer result */
            result_type res = result_type::OK;
            /* create token to pass into lexer */
            token tok{};

            for(;;) {
                res = lexer.next(tok);
                switch (res) {
                    case result_type::OK:
                        updateAst(tok);
                        break;
                    case result_type::DONE:
                        {
                        ast_node program(new ast_program(tok.loc, astSeq));
                        return program;
                        }
                    case result_type::FAIL:
                    default:
                        break;
                }
            }
        }

    private:

        Lexer lexer;

        /* vector of instructions to return */
        ast_seq astSeq;

        ast_node updateLoop(source_loc loopPos){
            /* create result to hold lexer result */
            result_type res = result_type::OK;
            /* create token to pass into lexer */
            token tok;
            /* create vector to use to create ast_loop */
            ast_seq loopAst{};

            for(;;) {
                res = lexer.next(tok);
                token::type kind = tok.kind;
                source_loc loc = tok.loc;
                switch (res) {
                    case result_type::OK:
                        switch (kind) {
                            case token::INC:
                              {
                                ast_node add(new ast_add(loc, 0, 1));
                                loopAst.push_back(add);
                                break;
                              }
                            case token::DEC:
                              {
                                ast_node sub(new ast_sub(loc, 0, 1));
                                loopAst.push_back(sub);
                                break;
                              }
                            case token::MOVE_R:
                              {
                                ast_node move_r(new ast_mov(loc, 1));
                                loopAst.push_back(move_r);
                                break;
                              }
                            case token::MOVE_L:
                              {
                                ast_node move_l(new ast_mov(loc, -1));
                                loopAst.push_back(move_l);
                                break;
                              }
                            case token::LOOP_BEGIN:
                              {
                                ast_node innerLoop = updateLoop(loc);
                                loopAst.push_back(innerLoop);
                                break;
                              }
                            case token::LOOP_END:
                              {
                                ast_node loop(new ast_loop(loopPos, loopAst));
                                return loop;
                              }
                            case token::PUT_CHAR:
                              {
                                ast_node write(new ast_write(loc, 0));
                                loopAst.push_back(write);
                                break;
                              }
                            case token::GET_CHAR:
                              {
                                ast_node read(new ast_read(loc, 0));
                                loopAst.push_back(read);
                                break;
                              }
                            default:
                                break;
                        }
                        break; /* result_type::OK */
                    case result_type::DONE:
                    case result_type::FAIL:
                    default:
                        break;
                        // Throw Exception (ends without closing loop)
                }
            }
        }

        void updateAst(token &tok) {
            token::type kind = tok.kind;
            source_loc loc = tok.loc;

            switch (kind) {
                case token::INC:
                  {
                    ast_node add(new ast_add(loc, 0, 1));
                    astSeq.push_back(add);
                    break;
                  }
                case token::DEC:
                  {
                    ast_node sub(new ast_sub(loc, 0, 1));
                    astSeq.push_back(sub);
                    break;
                  }
                case token::MOVE_R:
                  {
                    ast_node move_r(new ast_mov(loc, 1));
                    astSeq.push_back(move_r);
                    break;
                  }
                case token::MOVE_L:
                  {
                    ast_node move_l(new ast_mov(loc, -1));
                    astSeq.push_back(move_l);
                    break;
                  }
                case token::LOOP_BEGIN:
                  {
                    ast_node loop = updateLoop(loc);
                    astSeq.push_back(loop);
                    break;
                  }
                case token::LOOP_END:
                    // Throw Exception (No open loop to close)
                  break;
                case token::PUT_CHAR:
                  {
                    ast_node write(new ast_write(loc, 0));
                    astSeq.push_back(write);
                    break;
                  }
                case token::GET_CHAR:
                  {
                    ast_node read(new ast_read(loc, 0));
                    astSeq.push_back(read);
                    break;
                  }
                default:
                    break;
            }
        }

};

}

#endif /* !BFC_PARSER_HPP */
