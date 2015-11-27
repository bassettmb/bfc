#ifndef BFC_AST_MOD_HPP
#define BFC_AST_MOD_HPP

#include "types.h"

#include "ast/base.hpp"
#include "ast/seq.hpp"
#include "ast/traits.hpp"
#include "ast/visitor.hpp"
#include "token.hpp"

#include <cstddef>

namespace bfc {
namespace ast {

/* NB: when adding visitable node types, make sure you add a forward
 * declaration in "ast/visitor.hpp" and a visit overload on the visitor
 * abstract class.
 */

class add : public base_crtp<add>, public arith {
public:
  add(sourceloc loc, ptrdiff_t offset, bf_value value) noexcept :
    arith{std::move(loc), offset, value}
  {}
};

class sub : public base_crtp<sub>, public arith {
public:
  sub(sourceloc loc, ptrdiff_t offset, bf_value value) noexcept :
    arith{std::move(loc), offset, value}
  {}
};


class mul : public base_crtp<mul>, public arith {
public:
  mul(sourceloc loc, ptrdiff_t offset, bf_value value) noexcept :
    arith{std::move(loc), offset, value}
  {}
};

class mov : public base_crtp<mov>, public ptr_op {
public:
  mov(sourceloc loc, ptrdiff_t offset) noexcept :
    ptr_op{std::move(loc), offset}
  {}
};

class program : public has_loc, public seq {
public:
  program(sourceloc loc, seq op_seq) noexcept :
    has_loc{std::move(loc)}, seq{std::move(op_seq)}
  {}
};

class loop : public has_loc, public seq {
public:
  loop(sourceloc begin_pos, seq op_seq) noexcept :
    has_loc{begin_pos}, seq{std::move(op_seq)}
  {}
};

class read : public io {
public:
  read(sourceloc loc, ptrdiff_t offset) noexcept :
    io{std::move(loc), offset}
  {}
};

class write : public io {
public:
  write(sourceloc loc, ptrdiff_t offset) noexcept :
    io{std::move(loc), offset}
  {}
};

}
}

#endif /* !BFC_AST_HPP */
