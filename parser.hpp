#ifndef BFC_PARSER_HPP
#define BFC_PARSER_HPP

#include "lexer.hpp"
#include "result.hpp"
#include "ast.hpp"

namespace bfc {

template <class Source, class Traits = source_traits<Source>>
class Parser {

    public:

        using Lexer = lexer<Source, Traits>;

        Parser(Lexer lexer) : lexer(std::move(lexer)) {}

        ast_program parse() {
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
                        ast_program program(tok.loc, astSeq);
                        return program;
                    case result_type::FAIL:
                    default:
                }
            }
        }

    private:

        Lexer lexer;

        /* vector of instructions to return */
        ast_seq astSeq;

        ast_loop updateLoop(source_loc loopPos){
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
                                ast_add add(loc, 0, 1);
                                loopAst.push_back(add);
                                break;
                              }
                            case token::DEC:
                              {
                                ast_sub sub(loc, 0, 1);
                                loopAst.push_back(sub);
                                break;
                              }
                            case token::MOVE_R:
                              {
                                ast_mov move_r(loc, 1);
                                loopAst.push_back(move_r);
                                break;
                              }
                            case token::MOVE_L:
                              {
                                ast_mov move_l(loc, -1);
                                loopAst.push_back(move_l);
                                break;
                              }
                            case token::LOOP_BEGIN:
                              {
                                ast_loop innerLoop = updateLoop(loc);
                                loopAst.push_back(innerLoop);
                                break;
                              }
                            case token::LOOP_END:
                              {
                                ast_loop loop(loopPos, loopAst);
                                return loop;
                              }
                            case token::PUT_CHAR:
                              {
                                ast_write write(loc, 0);
                                loopAst.push_back(write);
                                break;
                              }
                            case token::GET_CHAR:
                              {
                                ast_read read(loc, 0);
                                loopAst.push_back(read);
                                break;
                              }
                            default:
                        }
                        break; /* result_type::OK */
                    case result_type::DONE:
                    case result_type::FAIL:
                    default:
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
                    ast_add add(loc, 0, 1);
                    astSeq.push_back(add);
                    break;
                  }
                case token::DEC:
                  {
                    ast_sub sub(loc, 0, 1);
                    astSeq.push_back(sub);
                    break;
                  }
                case token::MOVE_R:
                  {
                    ast_mov move_r(loc, 1);
                    astSeq.push_back(move_r);
                    break;
                  }
                case token::MOVE_L:
                  {
                    ast_mov move_l(loc, -1);
                    astSeq.push_back(move_l);
                    break;
                  }
                case token::LOOP_BEGIN:
                  {
                    ast_loop loop = updateLoop(loc);
                    astSeq.push_back(loop);
                    break;
                  }
                case token::LOOP_END:
                    // Throw Exception (No open loop to close)
                  break;
                case token::PUT_CHAR:
                  {
                    ast_write write(loc, 0);
                    astSeq.push_back(write);
                    break;
                  }
                case token::GET_CHAR:
                  {
                    ast_read read(loc, 0);
                    astSeq.push_back(read);
                    break;
                  }
                default:

            }
        }

};

}

#endif /* !BFC_PARSER_HPP */
