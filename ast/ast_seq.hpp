#ifndef AST_SEQ_HPP
#define AST_SEQ_HPP

#include "ast/ast_base.hpp"
#include "ast/ast_visitor.hpp"
#include <deque>

namespace bfc {

class ast_seq : public ast_base {

  using container = std::deque<ast_node>;

public:

  using size_type = typename container::size_type;
  using iterator = typename container::iterator;
  using const_iterator = typename container::const_iterator;

  ast_seq(void);

  template <class InputIt>
  ast_seq(InputIt begin, InputIt end);

  void swap(ast_seq &other) noexcept;

  iterator begin(void) noexcept;
  const_iterator begin(void) const noexcept;
  const_iterator cbegin(void) const noexcept;

  iterator end(void) noexcept;
  const_iterator end(void) const noexcept;
  const_iterator cend(void) const noexcept;

  ast_node &front(void) noexcept;
  const ast_node &front(void) const noexcept;
  ast_node &back(void) noexcept;
  const ast_node &back(void) const noexcept;
  bool empty(void) const noexcept;
  size_type size(void) const noexcept;

  void clear(void) noexcept;
  iterator insert(const_iterator it, ast_node elem);
  template <class InputIt>
  iterator insert(const_iterator it, InputIt first, InputIt last);
  template <class ...Args>
  iterator emplace(const_iterator it, Args &&...args);
  iterator remove(const_iterator it) noexcept;
  iterator remove(const_iterator first, const_iterator last) noexcept;

  void push_front(ast_node node);
  void push_back(ast_node node);
  void pop_front(void) noexcept;
  void pop_back(void) noexcept;

  template <class ...Args>
  void emplace_front(Args &&...args);

  template <class ...Args>
  void emplace_back(Args &&...args);


  ast_visitor::status accept(ast_visitor &visitor) override;
  ast_visitor::status accept(ast_visitor &visitor) const override;
  ast_base *clone(void) const override;

private:

  container seq;

};

template <class InputIt>
ast_seq::ast_seq(InputIt first, InputIt last) : seq(first, last) {}

template <class InputIt>
ast_seq::iterator
ast_seq::insert(const_iterator it, InputIt first, InputIt last)
{
  return seq.insert(first, last);
}

template <class ...Args>
ast_seq::iterator
ast_seq::emplace(const_iterator it, Args &&...args)
{
  return seq.emplace(it, std::forward<Args>(args)...);
}

template <class ...Args>
void
ast_seq::emplace_front(Args &&...args)
{
  seq.emplace_front(std::forward<Args>(args)...);
}

template <class ...Args>
void
ast_seq::emplace_back(Args &&...args)
{
  seq.emplace_back(std::forward<Args>(args)...);
}

}

#endif /* !AST_SEQ_HPP */
