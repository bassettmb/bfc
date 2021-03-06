#ifndef BFC_PARSER_HPP
#define BFC_PARSER_HPP

#include <stdexcept>
#include <sstream>
#include "lexer.hpp"
#include "result.hpp"
#include "ast.hpp"

namespace bfc {

template <class Source, class Traits = source_traits<Source>>
class parser {

    public:

        using Lexer = lexer<Source, Traits>;

        parser(Lexer lexer) : lex(std::move(lexer)) {}

        ast_node parse() {
            /* create result to hold lexer result */
            result_type res;
            /* create token to pass into lexer */
            token tok{};

            for(;;) {
                res = lex.next(tok);
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
                        throw std::runtime_error("Error: Exception occured when reading input file");
                        break;
                } }
        }

    private:

        Lexer lex;

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
                res = lex.next(tok);
                token::type kind = tok.kind;
                source_loc loc = tok.loc;
                switch (res) {
                    case result_type::OK:
                        switch (kind) {
                            case token::INC:
                              {
                                loopAst.emplace_back(new ast_add(loc, 0, 1));
                                break;
                              }
                            case token::DEC:
                              {
                                loopAst.emplace_back(new ast_sub(loc, 0, 1));
                                break;
                              }
                            case token::MOVE_R:
                              {
                                loopAst.emplace_back(new ast_mov(loc, 1));
                                break;
                              }
                            case token::MOVE_L:
                              {
                                loopAst.emplace_back(new ast_mov(loc, -1));
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
                                loopAst.emplace_back(new ast_write(loc, 0));
                                break;
                              }
                            case token::GET_CHAR:
                              {
                                loopAst.emplace_back(new ast_read(loc, 0));
                                break;
                              }
                            default:
                                break;
                        }
                        break; /* result_type::OK */
                    case result_type::DONE:
                    case result_type::FAIL:
                    default:
                      {
                        std::stringstream msg;
                        msg << loopPos << ": unmatched \'[\'";
                        throw std::runtime_error(msg.str());
                        break;
                      }
                }
            }
        }

        void updateAst(token &tok) {
            token::type kind = tok.kind;
            source_loc loc = tok.loc;

            switch (kind) {
                case token::INC:
                  {
                    astSeq.emplace_back(new ast_add(loc, 0, 1));
                    break;
                  }
                case token::DEC:
                  {
                    astSeq.emplace_back(new ast_sub(loc, 0, 1));
                    break;
                  }
                case token::MOVE_R:
                  {
                    astSeq.emplace_back(new ast_mov(loc, 1));
                    break;
                  }
                case token::MOVE_L:
                  {
                    astSeq.emplace_back(new ast_mov(loc, -1));
                    break;
                  }
                case token::LOOP_BEGIN:
                  {
                    ast_node loop = updateLoop(loc);
                    astSeq.push_back(loop);
                    break;
                  }
                case token::LOOP_END:
                  {
                    std::stringstream msg;
                    msg << loc << ": unmatched \'[\'";
                    throw std::runtime_error(msg.str());
                    break;
                  }
                case token::PUT_CHAR:
                  {
                    astSeq.emplace_back(new ast_write(loc, 0));
                    break;
                  }
                case token::GET_CHAR:
                  {
                    astSeq.emplace_back(new ast_read(loc, 0));
                    break;
                  }
                default:
                    break;
            }
        }

};

}

#endif /* !BFC_PARSER_HPP */
