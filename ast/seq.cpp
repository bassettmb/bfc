#include "ast/seq.hpp"
#include <deque>

namespace bfc {
namespace ast {

seq::seq(void) = default;

seq::~seq(void) = default;

void seq::swap(seq &other) noexcept
{
  using std::swap;
  swap(elems, other.elems);
}

bool
seq::empty(void) const noexcept
{
  return elems.empty();
}

void
seq::clear(void) noexcept
{
  elems.clear();
}

seq::iterator
seq::insert(const_iterator it, node elem)
{
  return elems.insert(it, std::move(elem));
}

seq::iterator
seq::remove(const_iterator it) noexcept
{
  return elems.erase(it);
}

seq::iterator
seq::remove(const_iterator first, const_iterator last) noexcept
{
  return elems.erase(first, last);
}

void
seq::push_front(node elem)
{
  elems.push_front(std::move(elem));
}

void
seq::push_back(node elem)
{
  elems.push_back(std::move(elem));
}

void
seq::pop_front(void) noexcept
{
  elems.pop_front();
}

void
seq::pop_back(void) noexcept
{
  elems.pop_back();
}

seq::size_type
seq::size(void) const noexcept
{
  return elems.size();
}

seq::iterator
seq::begin(void) noexcept
{
  return elems.begin();
}

seq::const_iterator
seq::begin(void) const noexcept
{
  return elems.begin();
}

seq::const_iterator
seq::cbegin(void) const noexcept
{
  return elems.cbegin();
}

seq::iterator
seq::end(void) noexcept
{
  return elems.end();
}

seq::const_iterator
seq::end(void) const noexcept
{
  return elems.end();
}

seq::const_iterator
seq::cend(void) const noexcept
{
  return elems.cend();
}

visitor::status
seq::accept(visitor &visitor)
{
  /* FIXME: iterator invalidation! */
  auto status = visitor::CONTINUE;
  for (auto &elem : *this) {
    status = elem.accept(visitor);
    if (status == visitor::BREAK)
      break;
  }
  return status;
}

visitor::status
seq::accept(visitor &visitor) const
{
  /* FIXME: iterator invalidation! */
  auto status = visitor::CONTINUE;
  for (const auto &elem : *this) {
    status = elem.accept(visitor);
    if (status == visitor::BREAK)
      break;
  }
  return status;
}

base *
seq::clone(void) const
{
  return new seq{*this};
}

}
}
