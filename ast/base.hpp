#ifndef BFC_AST_BASE_HPP
#define BFC_AST_BASE_HPP

#include "ast/visitor.hpp"
#include <memory>

namespace bfc {
namespace ast {

class base;

class node {

public:

  constexpr node(void) noexcept;
  node(base *node) noexcept;
  node(const node &other);
  node(node &&other) noexcept;
  node &operator=(const node &other);
  node &operator=(node &&other) noexcept;
  ~node(void);
  void swap(node &other) noexcept;

  explicit operator bool(void) const noexcept;
  bool operator==(const node &other) const noexcept;
  bool operator!=(const node &other) const noexcept;
  bool operator==(base *other) const noexcept;
  bool operator!=(base *other) const noexcept;

  base *get(void) noexcept;
  const base *get(void) const noexcept;
  base *release(void) noexcept;
  void reset(base *ptr = nullptr) noexcept;

  visitor::status accept(visitor &visitor);
  visitor::status accept(visitor &visitor) const;

private:

  base *clone(void) const;
  std::unique_ptr<base> elem;

};

/* Clone was made private and node a friend of base to prevent misuse of
 * clone when constructing an AST. 
 */
class base {
  friend node;
public:
  virtual ~base(void) = default;
  virtual visitor::status accept(visitor &visitor) = 0;
  virtual visitor::status accept(visitor &visitor) const = 0;
private:
  virtual base *clone(void) const = 0;
};



}
}

#endif /* !BFC_AST_BASE_HPP */
