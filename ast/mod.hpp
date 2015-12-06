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

class set : public base_crtp<set>, public arith {
public:
  set(source_loc loc, ptrdiff_t offset, bf_value value) noexcept :
    arith{std::move(loc), offset, value}
  {}
};

class add : public base_crtp<add>, public arith {
public:
  add(source_loc loc, ptrdiff_t offset, bf_value value) noexcept :
    arith{std::move(loc), offset, value}
  {}
};

class sub : public base_crtp<sub>, public arith {
public:
  sub(source_loc loc, ptrdiff_t offset, bf_value value) noexcept :
    arith{std::move(loc), offset, value}
  {}
};


class mul : public base_crtp<mul>, public arith {
public:
  mul(source_loc loc, ptrdiff_t offset, bf_value value) noexcept :
    arith{std::move(loc), offset, value}
  {}
};

class mov : public base_crtp<mov>, public ptr_op {
public:
  mov(source_loc loc, ptrdiff_t offset) noexcept :
    ptr_op{std::move(loc), offset}
  {}
};

/* Cannot inherit from base_crtp because of the diamond problem. */
class program : public has_loc, public seq {
public:
  program(source_loc loc, seq op_seq) noexcept :
    has_loc{std::move(loc)}, seq{std::move(op_seq)}
  {}
  visitor::status accept(visitor &obj) override
  {
    return obj.visit(*this);
  }
  visitor::status accept(visitor &obj) const override
  {
    return obj.visit(*this);
  }
private:
  base *clone(void) const override
  {
    return new program{*this};
  }
};

/* Cannot inherit from base_crtp because of the diamond problem. */
class loop : public has_loc, public seq {
public:
  loop(source_loc begin_pos, seq op_seq) noexcept :
    has_loc{begin_pos}, seq{std::move(op_seq)}
  {}
  visitor::status accept(visitor &obj) override
  {
    return obj.visit(*this);
  }
  visitor::status accept(visitor &obj) const override
  {
    return obj.visit(*this);
  }
private:
  base *clone(void) const override
  {
    return new loop{*this};
  }
};

class read : public base_crtp<read>, public io {
public:
  read(source_loc loc, ptrdiff_t offset) noexcept :
    io{std::move(loc), offset}
  {}
};

class write : public base_crtp<write>, public io {
public:
  write(source_loc loc, ptrdiff_t offset) noexcept :
    io{std::move(loc), offset}
  {}
};

}
}

#endif /* !BFC_AST_HPP */
