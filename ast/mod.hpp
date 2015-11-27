#ifndef BFC_AST_MOD_HPP
#define BFC_AST_MOD_HPP

#include "types.h"

#include "ast/base.hpp"
#include "ast/seq.hpp"
#include "token.hpp"

#include <cstddef>

namespace bfc {
namespace ast {

/* NB: when adding visitable node types, make sure you add a forward
 * declaration in "ast/visitor.hpp" and a visit overload on the visitor
 * abstract class.
 */

class has_pos {
public:
  has_pos(position node_pos) noexcept : node_pos(node_pos) {}
  position pos(void) const noexcept { return node_pos; }
protected:
  ~has_pos() = default;
private:
  position node_pos;
};

class has_offset {
public:
  has_offset(ptrdiff_t node_offset) noexcept : node_offset(node_offset) {}
  ptrdiff_t offset(void) const noexcept { return node_offset; }
  void offset(ptrdiff_t new_offset) noexcept { node_offset = new_offset; }
protected:
  ~has_offset() = default;
private:
  ptrdiff_t node_offset;
};

class has_value {
public:
  has_value(bf_value node_value) noexcept : node_value(node_value) {}
  bf_value value(void) const noexcept { return node_value; }
  void value(bf_value value) noexcept { node_value = value; }
private:
  bf_value node_value;
};

class arith : public base, public has_pos,
                  public has_offset, public has_value {
public:
  arith(position pos, ptrdiff_t offset, bf_value value) noexcept :
    has_pos(pos), has_offset(offset), has_value(value)
  {}
protected:
  ~arith() = default;
};

class ptr_op : public base, public has_pos, public has_offset {
public:
  ptr_op(position pos, ptrdiff_t offset) noexcept :
    has_pos(pos), has_offset(offset)
  {}
protected:
  ~ptr_op() = default;
};

class io : public base, public has_pos, public has_offset {
public:
  io(position pos, ptrdiff_t offset) noexcept :
    has_pos(pos), has_offset(offset)
  {}
protected:
  ~io() = default;
};

class add : public arith {
public:
  add(position pos, ptrdiff_t offset, bf_value value) noexcept :
    arith(pos, offset, value)
  {}
  visitor::status accept(visitor &visitor) noexcept override
  {
    return visitor.visit(*this);
  }
  visitor::status accept(visitor &visitor) const noexcept override
  {
    return visitor.visit(*this);
  }
};

class sub : public arith {
public:
  sub(position pos, ptrdiff_t offset, bf_value value) noexcept :
    arith(pos, offset, value)
  {}
  visitor::status accept(visitor &visitor) noexcept override
  {
    return visitor.visit(*this);
  }
  visitor::status accept(visitor &visitor) const noexcept override
  {
    return visitor.visit(*this);
  }
};


class mul : public arith {
public:
  mul(position pos, ptrdiff_t offset, bf_value value) noexcept :
    arith(pos, offset, value)
  {}
  visitor::status accept(visitor &visitor) noexcept override
  {
    return visitor.visit(*this);
  }
  visitor::status accept(visitor &visitor) const noexcept override
  {
    return visitor.visit(*this);
  }
};

class mov : public ptr_op {
public:
  mov(position pos, ptrdiff_t offset) noexcept :
    ptr_op(pos, offset)
  {}
  visitor::status accept(visitor &visitor) noexcept override
  {
    return visitor.visit(*this);
  }
  visitor::status accept(visitor &visitor) const noexcept override
  {
    return visitor.visit(*this);
  }
};

class program : public has_pos, public seq {
public:
  program(position pos, seq op_seq) noexcept :
    has_pos(pos), seq(std::move(op_seq))
  {}
  visitor::status accept(visitor &visitor) noexcept override
  {
    return visitor.visit(*this);
  }
  visitor::status accept(visitor &visitor) const noexcept override
  {
    return visitor.visit(*this);
  }
};

class loop : public has_pos, public seq {
public:
  loop(position begin_pos, seq op_seq) noexcept :
    has_pos(begin_pos), seq(std::move(op_seq))
  {}
  visitor::status accept(visitor &visitor) noexcept override
  {
    return visitor.visit(*this);
  }
  visitor::status accept(visitor &visitor) const noexcept override
  {
    return visitor.visit(*this);
  }
};

class read : public io {
public:
  read(position pos, ptrdiff_t offset) noexcept : io(pos, offset) {}
  visitor::status accept(visitor &visitor) noexcept override
  {
    return visitor.visit(*this);
  }
  visitor::status accept(visitor &visitor) const noexcept override
  {
    return visitor.visit(*this);
  }
};

class write : public io {
public:
  write(position pos, ptrdiff_t offset) noexcept : io(pos, offset) {}
  visitor::status accept(visitor &visitor) noexcept override
  {
    return visitor.visit(*this);
  }
  visitor::status accept(visitor &visitor) const noexcept override
  {
    return visitor.visit(*this);
  }
};

}
}

#endif /* !BFC_AST_HPP */
