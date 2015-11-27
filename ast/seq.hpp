#ifndef BFC_AST_SEQ_HPP
#define BFC_AST_SEQ_HPP

#include "ast/base.hpp"
#include "ast/visitor.hpp"
#include <deque>

namespace bfc {
namespace ast {

class seq : public base {

  using container = std::deque<node>;

public:

  using size_type = typename container::size_type;
  using iterator = typename container::iterator;
  using const_iterator = typename container::const_iterator;

  seq(void);

  template <class InputIt>
  seq(InputIt begin, InputIt end);

  void swap(seq &other) noexcept;

  iterator begin(void) noexcept;
  const_iterator begin(void) const noexcept;
  const_iterator cbegin(void) const noexcept;

  iterator end(void) noexcept;
  const_iterator end(void) const noexcept;
  const_iterator cend(void) const noexcept;

  node &front(void) noexcept;
  const node &front(void) const noexcept;
  node &back(void) noexcept;
  const node &back(void) const noexcept;
  bool empty(void) const noexcept;
  size_type size(void) const noexcept;

  void clear(void) noexcept;
  iterator insert(const_iterator it, node elem);
  template <class InputIt>
  iterator insert(const_iterator it, InputIt first, InputIt last);
  template <class ...Args>
  iterator emplace(const_iterator it, Args &&...args);
  iterator remove(const_iterator it) noexcept;
  iterator remove(const_iterator first, const_iterator last) noexcept;

  void push_front(node node);
  void push_back(node node);
  void pop_front(void) noexcept;
  void pop_back(void) noexcept;

  template <class ...Args>
  void emplace_front(Args &&...args);

  template <class ...Args>
  void emplace_back(Args &&...args);


  visitor::status accept(visitor &visitor) override;
  visitor::status accept(visitor &visitor) const override;

private:

  base *clone(void) const override;
  container elems;

};

template <class InputIt>
seq::seq(InputIt first, InputIt last) : elems(first, last) {}

template <class InputIt>
seq::iterator
seq::insert(const_iterator it, InputIt first, InputIt last)
{
  return elems.insert(it, first, last);
}

template <class ...Args>
seq::iterator
seq::emplace(const_iterator it, Args &&...args)
{
  return elems.emplace(it, std::forward<Args>(args)...);
}

template <class ...Args>
void
seq::emplace_front(Args &&...args)
{
  elems.emplace_front(std::forward<Args>(args)...);
}

template <class ...Args>
void
seq::emplace_back(Args &&...args)
{
  elems.emplace_back(std::forward<Args>(args)...);
}

}
}

#endif /* !BFC_AST_SEQ_HPP */
