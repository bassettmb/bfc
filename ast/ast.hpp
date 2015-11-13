#ifndef BFC_AST_HPP
#define BFC_AST_HPP

#include "types.h"

#include "ast/ast_base.hpp"
#include "ast/ast_seq.hpp"
#include "token.hpp"

#include <cstddef>

namespace bfc {

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

class ast_arith : public ast_base, public has_pos,
                  public has_offset, public has_value {
public:
  ast_arith(position pos, ptrdiff_t offset, bf_value value) noexcept :
    has_pos(pos), has_offset(offset), has_value(value)
  {}
protected:
  ~ast_arith() = default;
};

class ast_ptr_op : public ast_base, public has_pos, public has_offset {
public:
  ast_ptr_op(position pos, ptrdiff_t offset) noexcept :
    has_pos(pos), has_offset(offset)
  {}
protected:
  ~ast_ptr_op() = default;
};

class ast_io : public ast_base, public has_pos, public has_offset {
public:
  ast_io(position pos, ptrdiff_t offset) noexcept :
    has_pos(pos), has_offset(offset)
  {}
protected:
  ~ast_io() = default;
};

class ast_add : public ast_arith {
public:
  ast_add(position pos, ptrdiff_t offset, bf_value value) noexcept :
    ast_arith(pos, offset, value)
  {}
  ast_visitor::status accept(ast_visitor &visitor) noexcept override
  {
    return visitor.visit(*this);
  }
  ast_visitor::status accept(ast_visitor &visitor) const noexcept override
  {
    return visitor.visit(*this);
  }
};

class ast_sub : public ast_arith {
public:
  ast_sub(position pos, ptrdiff_t offset, bf_value value) noexcept :
    ast_arith(pos, offset, value)
  {}
  ast_visitor::status accept(ast_visitor &visitor) noexcept override
  {
    return visitor.visit(*this);
  }
  ast_visitor::status accept(ast_visitor &visitor) const noexcept override
  {
    return visitor.visit(*this);
  }
};


class ast_mul : public ast_arith {
public:
  ast_mul(position pos, ptrdiff_t offset, bf_value value) noexcept :
    ast_arith(pos, offset, value)
  {}
  ast_visitor::status accept(ast_visitor &visitor) noexcept override
  {
    return visitor.visit(*this);
  }
  ast_visitor::status accept(ast_visitor &visitor) const noexcept override
  {
    return visitor.visit(*this);
  }
};

class ast_mov : public ast_ptr_op {
public:
  ast_mov(position pos, ptrdiff_t offset) noexcept :
    ast_ptr_op(pos, offset)
  {}
  ast_visitor::status accept(ast_visitor &visitor) noexcept override
  {
    return visitor.visit(*this);
  }
  ast_visitor::status accept(ast_visitor &visitor) const noexcept override
  {
    return visitor.visit(*this);
  }
};

class ast_program : public has_pos, public ast_seq {
public:
  ast_program(position pos, ast_seq op_seq) noexcept :
    has_pos(pos), ast_seq(std::move(op_seq))
  {}
  ast_visitor::status accept(ast_visitor &visitor) noexcept override
  {
    return visitor.visit(*this);
  }
  ast_visitor::status accept(ast_visitor &visitor) const noexcept override
  {
    return visitor.visit(*this);
  }
};

class ast_loop : public has_pos, public ast_seq {
public:
  ast_loop(position begin_pos, ast_seq ops) noexcept :
    has_pos(begin_pos), ast_seq(std::move(op_seq))
  {}
  ast_visitor::status accept(ast_visitor &visitor) noexcept override
  {
    return visitor.visit(*this);
  }
  ast_visitor::status accept(ast_visitor &visitor) const noexcept override
  {
    return visitor.visit(*this);
  }
};

class ast_read : public ast_io {
public:
  ast_read(position pos, ptrdiff_t offset) noexcept : ast_io(pos, offset) {}
  ast_visitor::status accept(ast_visitor &visitor) noexcept override
  {
    return visitor.visit(*this);
  }
  ast_visitor::status accept(ast_visitor &visitor) const noexcept override
  {
    return visitor.visit(*this);
  }
};

class ast_write : public ast_io {
public:
  ast_write(position pos, ptrdiff_t offset) noexcept : ast_io(pos, offset) {}
  ast_visitor::status accept(ast_visitor &visitor) noexcept override
  {
    return visitor.visit(*this);
  }
  ast_visitor::status accept(ast_visitor &visitor) const noexcept override
  {
    return visitor.visit(*this);
  }
};

}

#endif /* !BFC_AST_HPP */
