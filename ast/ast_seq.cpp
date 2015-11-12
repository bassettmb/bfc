#include "ast_seq.hpp"
#include <deque>

namespace bfc {

ast_seq::ast_seq(void) {}

void ast_seq::swap(ast_seq &other) noexcept
{
  using std::swap;
  swap(seq, other.seq);
}

bool
ast_seq::empty(void) const noexcept
{
  return seq.empty();
}

void
ast_seq::clear(void) noexcept
{
  seq.clear();
}

ast_seq::iterator
ast_seq::insert(const_iterator it, ast_node node)
{
  return seq.insert(it, std::move(node));
}

ast_seq::iterator
ast_seq::remove(const_iterator it) noexcept
{
  return seq.erase(it);
}

ast_seq::iterator
ast_seq::remove(const_iterator first, const_iterator last) noexcept
{
  return seq.erase(first, last);
}

void
ast_seq::push_front(ast_node node)
{
  seq.push_front(std::move(node));
}

void
ast_seq::push_back(ast_node node)
{
  seq.push_back(std::move(node));
}

void
ast_seq::pop_front(void) noexcept
{
  seq.pop_front();
}

void
ast_seq::pop_back(void) noexcept
{
  seq.pop_back();
}

ast_seq::size_type
ast_seq::size(void) const noexcept
{
  return seq.size();
}

ast_seq::iterator
ast_seq::begin(void) noexcept
{
  return seq.begin();
}

ast_seq::const_iterator
ast_seq::begin(void) const noexcept
{
  return seq.begin();
}

ast_seq::const_iterator
ast_seq::cbegin(void) const noexcept
{
  return seq.cbegin();
}

ast_seq::iterator
ast_seq::end(void) noexcept
{
  return seq.end();
}

ast_seq::const_iterator
ast_seq::end(void) const noexcept
{
  return seq.end();
}

ast_seq::const_iterator
ast_seq::cend(void) const noexcept
{
  return seq.cend();
}

ast_visitor::status
ast_seq::accept(ast_visitor &visitor)
{
  ast_visitor::status status = ast_visitor::CONTINUE;
  for (ast_node &node : *this) {
    status = node.accept(visitor);
    if (status == ast_visitor::BREAK)
      break;
  }
  return status;
}

ast_visitor::status
ast_seq::accept(ast_visitor &visitor) const
{
  ast_visitor::status status = ast_visitor::CONTINUE;
  for (const ast_node &node : *this) {
    status = node.accept(visitor);
    if (status == ast_visitor::BREAK)
      break;
  }
  return status;
}

ast_base *
ast_seq::clone(void) const
{
  return new ast_seq(*this);
}

}
