#ifndef BFC_AST_TRAITS_HPP
#define BFC_AST_TRAITS_HPP

#include "types.h"
#include "ast/base.hpp"
#include "ast/seq.hpp"
#include "ast/visitor.hpp"
#include "source_loc.hpp"
#include <cstddef>

namespace bfc {
namespace ast {

/* Default implementations for accept and clone. We use the CRTP to avoid
 * having to define boilerplate for each class. To use these defaults,
 * inherit from base_crtp.
 */
template <class derived_type>
class base_crtp : public base {
public:
  visitor::status accept(visitor &obj) override
  {
    return obj.visit(reinterpret_cast<derived_type &>(*this));
  }
  visitor::status accept(visitor &obj) const override
  {
    return obj.visit(reinterpret_cast<const derived_type &>(*this));
  }
private:
  base *clone(void) const override
  {
    return new derived_type(reinterpret_cast<const derived_type &>(*this));
  }
};

/* Trait for nodes having a source position. */
class has_loc {
public:
  has_loc(source_loc node_loc) noexcept : node_loc{std::move(node_loc)} {}
  source_loc loc(void) const noexcept { return node_loc; }
protected:
  ~has_loc() = default;
private:
  source_loc node_loc;
};

/* Trait for nodes holding an offset (to the brainfuck heap pointer). */
class has_offset {
public:
  has_offset(ptrdiff_t node_offset) noexcept : node_offset{node_offset} {}
  ptrdiff_t offset(void) const noexcept { return node_offset; }
  void offset(ptrdiff_t new_offset) noexcept { node_offset = new_offset; }
protected:
  ~has_offset() = default;
private:
  ptrdiff_t node_offset;
};

/* Trait for nodes holding a (brainfuck) value. */
class has_value {
public:
  has_value(bf_value node_value) noexcept : node_value{node_value} {}
  bf_value value(void) const noexcept { return node_value; }
  void value(bf_value value) noexcept { node_value = value; }
private:
  bf_value node_value;
};

/* Abstract base class for arithmetic operation nodes. */
class arith : public has_loc, public has_offset, public has_value {
public:
  arith(source_loc loc, ptrdiff_t offset, bf_value value) noexcept :
    has_loc{loc}, has_offset{offset}, has_value{value}
  {}
protected:
  ~arith() = default;
};

/* Abstract base class for pointer arithmetic operation nodes. */
class ptr_op : public has_loc, public has_offset {
public:
  ptr_op(source_loc loc, ptrdiff_t offset) noexcept :
    has_loc{loc}, has_offset{offset}
  {}
protected:
  ~ptr_op() = default;
};

/* Abstract base class for io operation nodes. */
class io : public base, public has_loc, public has_offset {
public:
  io(source_loc loc, ptrdiff_t offset) noexcept :
    has_loc{std::move(loc)}, has_offset{offset}
  {}
protected:
  ~io() = default;
};

}
}

#endif /* !BFC_AST_TRAITS_HPP */
