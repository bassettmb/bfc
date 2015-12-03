#include "ast/base.hpp"
#include <utility>
#include <iostream>

namespace bfc {
namespace ast {

constexpr node::node(void) noexcept : elem(nullptr) {}
node::node(base *elem) noexcept : elem(elem) {}
node::node(const node &other) : elem(other.clone()) {}
node::node(node &&other) noexcept : elem(std::move(other.elem)) {}

node &
node::operator=(const node &other)
{
  if (this != &other)
    reset(other.clone());
  return *this;
}

node &
node::operator=(node &&other) noexcept
{
  reset(other.release());
  return *this;
}

node::~node(void) = default;

node::operator bool(void) const noexcept
{
  return static_cast<bool>(elem);
}

bool
node::operator==(const node &other) const noexcept
{
  return *this == other.elem.get();
}

bool
node::operator!=(const node &other) const noexcept
{
  return *this != other.elem.get();
}

bool
node::operator==(base *other) const noexcept
{
  return elem.get() == other;
}

bool
node::operator!=(base *other) const noexcept
{
  return elem.get() != other;
}

void
node::swap(node &other) noexcept
{
  using std::swap;
  swap(elem, other.elem);
}

base *
node::get(void) noexcept
{
  return elem.get();
}

const base *
node::get(void) const noexcept
{
  return elem.get();
}

base *
node::release(void) noexcept
{
  return elem.release();
}

void
node::reset(base *ptr) noexcept
{
  elem.reset(ptr);
}

visitor::status
node::accept(visitor &visitor)
{
  return elem->accept(visitor);
}


visitor::status
node::accept(visitor &visitor) const
{
  /* This cast is necessary because otherwise we manage a turn const pointer
   * non-const and why the hell fuck.
   */
  return static_cast<const base *>(elem.get())->accept(visitor);
}

base *
node::clone(void) const
{
  return elem->clone();
}

}
}
