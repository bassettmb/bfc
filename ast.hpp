#ifndef BFC_AST_HPP
#define BFC_AST_HPP

/* Header providing access to AST. */

#include "ast/mod.hpp"
#include "ast/visitor.hpp"

namespace bfc {

using ast_node = ast::node;

using ast_program = ast::program;
using ast_loop = ast::loop;

using ast_mov = ast::mov;
using ast_add = ast::add;
using ast_sub = ast::sub;
using ast_mul = ast::mul;
using ast_set = ast::set;

using ast_read = ast::read;
using ast_write = ast::write;

using ast_seq = ast::seq;
}

#endif /* !BFC_AST_HPP */
