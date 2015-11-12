#ifndef BFC_AST_BASE_HPP
#define BFC_AST_BASE_HPP

#include "ast_visitor.hpp"
#include <memory>

namespace bfc {

class ast_base {
public:
  virtual ~ast_base(void) = default;
  virtual ast_base *clone(void) const = 0;
  virtual ast_visitor::status accept(ast_visitor &visitor) = 0;
  virtual ast_visitor::status accept(ast_visitor &visitor) const = 0;
};

class ast_node {

public:

  constexpr ast_node(void) noexcept;
  ast_node(ast_base *node) noexcept;
  ast_node(const ast_node &other);
  ast_node(ast_node &&other) noexcept;
  ast_node &operator=(const ast_node &other);
  ast_node &operator=(ast_node &&other) noexcept;
  ~ast_node(void);
  void swap(ast_node &other) noexcept;

  explicit operator bool(void) const noexcept;
  bool operator==(const ast_node &other) const noexcept;
  bool operator!=(const ast_node &other) const noexcept;
  bool operator==(ast_base *other) const noexcept;
  bool operator!=(ast_base *other) const noexcept;

  ast_base *get(void) noexcept;
  const ast_base *get(void) const noexcept;
  ast_base *release(void) noexcept;
  void reset(ast_base *ptr = nullptr) noexcept;

  ast_visitor::status accept(ast_visitor &visitor);
  ast_visitor::status accept(ast_visitor &visitor) const;

private:

  ast_base *clone(void) const;
  std::unique_ptr<ast_base> node;

};

}

#endif /* !BFC_AST_BASE_HPP */
