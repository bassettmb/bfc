#ifndef BFC_OPTS_HPP
#define BFC_OPTS_HPP

/* Header providing access to optimizing visitors. */

#include "opts/opt_program_visitor.hpp"
#include "opts/opt_seq_base_visitor.hpp"
#include "opts/clear_loops_visitor.hpp"
#include "opts/combine_inc_visitor.hpp"
#include "opts/combine_ptr_visitor.hpp"
#include "opts/combine_set_visitor.hpp"
#include "opts/dead_loops_visitor.hpp"
#include "opts/dead_set_visitor.hpp"
#include "opts/mul_loops_visitor.hpp"

namespace bfc {

using opt_program_visitor = ast::opt_program_visitor;
using opt_seq_base_visitor = ast::opt_seq_base_visitor;

using combine_inc_visitor = ast::combine_inc_visitor;
using combine_ptr_visitor = ast::combine_ptr_visitor;
using combine_set_visitor = ast::combine_set_visitor;

using clear_loops_visitor = ast::clear_loops_visitor;
using mul_loops_visitor = ast::mul_loops_visitor;

using dead_loops_visitor = ast::dead_loops_visitor;
using dead_set_visitor = ast::dead_set_visitor;

}

#endif /* !BFC_OPTS_HPP */
