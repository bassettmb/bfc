#include "ast/ast_base.hpp"
#include <utility>

namespace bfc {

constexpr ast_node::ast_node(void) noexcept : node(nullptr) {}
ast_node::ast_node(ast_base *node) noexcept : node(node) {}
ast_node::ast_node(const ast_node &other) : node(other.clone()) {}
ast_node::ast_node(ast_node &&other) noexcept : node(std::move(other.node)) {}

ast_node &
ast_node::operator=(const ast_node &other)
{
  if (this != &other)
    reset(other.clone());
  return *this;
}

ast_node &
ast_node::operator=(ast_node &&other) noexcept
{
  reset(other.release());
  return *this;
}

ast_node::~ast_node(void) = default;

ast_node::operator bool(void) const noexcept
{
  return static_cast<bool>(node);
}

bool
ast_node::operator==(const ast_node &other) const noexcept
{
  return *this == other.node.get();
}

bool
ast_node::operator!=(const ast_node &other) const noexcept
{
  return *this != other.node.get();
}

bool
ast_node::operator==(ast_base *other) const noexcept
{
  return node.get() == other;
}

bool
ast_node::operator!=(ast_base *other) const noexcept
{
  return node.get() != other;
}

void
ast_node::swap(ast_node &other) noexcept
{
  using std::swap;
  swap(node, other.node);
}

ast_base *
ast_node::get(void) noexcept
{
  return node.get();
}

const ast_base *
ast_node::get(void) const noexcept
{
  return node.get();
}

ast_base *
ast_node::release(void) noexcept
{
  return node.release();
}

void
ast_node::reset(ast_base *ptr) noexcept
{
  node.reset(ptr);
}

ast_visitor::status
ast_node::accept(ast_visitor &visitor)
{
  return node->accept(visitor);
}

ast_visitor::status
ast_node::accept(ast_visitor &visitor) const
{
  return node->accept(visitor);
}

ast_base *
ast_node::clone(void) const
{
  return node->clone();
}

}
