#include "pprint/c_pprint.hpp"

#include <ostream>
#include <string>
#include <vector>
#include <stdexcept>

namespace bfc {
namespace pprint {

c_pprint::c_pprint(void) = default;

c_pprint::config::config(void) :
  prelude{
    "#include \"bfc_rts.h\"",
    "void bfc_main(void) {"
  },
  postlude {
    "  (void)(0);",
    "}"
  },
  label_prefix{"bfc_l"},
  hp_iden{"bfc_hp"},
  mov_iden{"bfc_mov"},
  getc_iden{"bfc_getc"},
  putc_iden{"bfc_putc"},
  add_iden{"bfc_add"},
  sub_iden{"bfc_sub"},
  mul_iden{"bfc_mul"},
  set_iden{"bfc_set"}
{}

namespace {

class pp_delegate : public ast::visitor {

  using label_id = unsigned long;

public:

  pp_delegate(std::ostream &out, const c_pprint::config &opts) :
    ast::visitor{}, next_label_id{0}, opts{opts}, sink{out}
  {}

  void emit(const ast::node &node)
  {
    node.accept(*this);
  }

  ast::visitor::status visit(const ast::program &prgm) override
  {
    pp_prelude();
    for (auto &node: prgm)
      node.accept(*this);
    pp_postlude();
    return ast::visitor::CONTINUE;
  }

  ast::visitor::status visit(const ast::loop &loop) override
  {
    auto begin_id = get_label();
    auto end_id = get_label();
    pp_label(begin_id);
    pp_bez(end_id);
    for (auto &node: loop)
      node.accept(*this);
    pp_bnz(begin_id);
    pp_label(end_id);
    return ast::visitor::CONTINUE;
  }

  ast::visitor::status visit(const ast::add &node) override
  {
    pp_add(node.offset(), node.value());
    return ast::visitor::CONTINUE;
  }

  ast::visitor::status visit(const ast::sub &node) override
  {
    pp_sub(node.offset(), node.value());
    return ast::visitor::CONTINUE;
  }

  ast::visitor::status visit(const ast::mul &node) override
  {
    pp_mul(node.offset(), node.value());
    return ast::visitor::CONTINUE;
  }

  ast::visitor::status visit(const ast::set &node) override
  {
    pp_set(node.offset(), node.value());
    return ast::visitor::CONTINUE;
  }

  ast::visitor::status visit(const ast::mov &node) override
  {
    pp_mov(node.offset());
    return ast::visitor::CONTINUE;
  }

  ast::visitor::status visit(const ast::read &node) override
  {
    pp_getc(node.offset());
    return ast::visitor::CONTINUE;
  }

  ast::visitor::status visit(const ast::write &node) override
  {
    pp_putc(node.offset());
    return ast::visitor::CONTINUE;
  }

private:

  label_id get_label(void) noexcept
  {
    auto id = next_label_id;
    next_label_id += 1;
    return id;
  }

  void pp_indent(void) const
  {
    sink << ' ' << ' ';
  }

  void pp_indent(unsigned long nlevels) const
  {
    while (nlevels--)
      pp_indent();
  }

  template <class InputIt>
  void pp_iter(InputIt begin, InputIt end) const
  {
    for (; begin != end; ++begin)
      sink << *begin << std::endl;
  }

  void pp_label_name(unsigned long id)
  {
    sink << opts.label_prefix << id;
  }

  void pp_label(unsigned long id)
  {
    pp_label_name(id);
    sink << ':' << std::endl;
  }

  void pp_jump(unsigned long id)
  {
    pp_indent();
    sink << "goto ";
    pp_label_name(id);
    sink << ';' << std::endl;
  }

  void pp_bez(label_id id)
  {
    pp_branch(id, true);
  }

  void pp_bnz(label_id id)
  {
    pp_branch(id, false);
  }

  void pp_branch(label_id id, bool invert)
  {
    pp_indent();
    sink << "if (";
    if (invert)
      sink << '!';
    sink << "*" << opts.hp_iden;
    sink << ')' << std::endl;
    pp_indent(2);
    pp_jump(id);
  }

  void pp_fn(const char *fn)
  {
    pp_indent();
    sink << fn << "();" << std::endl;
  }

  template <class Arg>
  void pp_fn(const char *fn, Arg &&arg)
  {
    pp_indent();
    sink << fn << '(' << arg << ");" << std::endl;
  }

  template <class Arg, class ...Args>
  void pp_fn(const char *fn, Arg &&arg, Args &&...args)
  {
    pp_indent();
    sink << fn << '(' << std::forward<Arg>(arg);
    pp_fn_recur(std::forward<Args>(args)...);
    sink << ");" << std::endl;
  }

  template <class Arg>
  void pp_fn_recur(Arg &&arg)
  {
    sink << ", " << std::forward<Arg>(arg);
  }

  template <class Arg, class ...Args>
  void pp_fn_recur(Arg &&arg, Args &&...args)
  {
    sink << ", " << std::forward<Arg>(arg);
    pp_fn_recur(std::forward<Args>(args)...);
  }

  void pp_prelude(void) const
  {
    auto &vec = opts.prelude;
    pp_iter(vec.begin(), vec.end());
  }

  void pp_postlude(void) const
  {
    auto &vec = opts.postlude;
    pp_iter(vec.begin(), vec.end());
  }

  void pp_add(ptrdiff_t offset, int value)
  {
    pp_indent();
    pp_fn(opts.add_iden.data(), offset, value);
  }

  void pp_sub(ptrdiff_t offset, int value)
  {
    pp_indent();
    pp_fn(opts.sub_iden.data(), offset, value);
  }

  void pp_mul(ptrdiff_t offset, int value)
  {
    pp_indent();
    pp_fn(opts.mul_iden.data(), offset, value);
  }

  void pp_set(ptrdiff_t offset, int value)
  {
    pp_indent();
    pp_fn(opts.set_iden.data(), offset, value);
  }

  void pp_getc(ptrdiff_t offset)
  {
    pp_indent();
    pp_fn(opts.getc_iden.data(), offset);
  }

  void pp_putc(ptrdiff_t offset)
  {
    pp_indent();
    pp_fn(opts.putc_iden.data(), offset);
  }

  void pp_mov(ptrdiff_t offset)
  {
    pp_indent();
    pp_fn(opts.mov_iden.data(), offset);
  }

  void pp_set(ptrdiff_t offset, int value)
  {
    pp_indent();
    pp_fn(opts.set_iden.data(), offset, value);
  }

  label_id next_label_id;
  const c_pprint::config &opts;
  std::ostream &sink;

};
}

void
c_pprint::emit(std::ostream &out, const ast::node &node)
{
  auto pp = pp_delegate{out, opts};
  pp.emit(node);
}

}
}
