#ifndef BFC_PPRINT_HPP
#define BFC_PPRINT_HPP

#include "pprint/sink.hpp"

#include <cerrno>
#include <ostream>
#include <string>
#include <system_error>
#include <vector>

namespace bfc {
namespace pprint {

struct c_pprint_opts {
  std::vector<std::string> prelude;
  std::vector<std::string> postlude;
  std::string label_prefix;
  std::string hp_iden;
  std::string mov_fn;
  std::string getc_fn;
  std::string putc_fn;
};

class c_pprint : public ast::visitor {

  using label_id = unsigned long;

public:

  explicit c_pprint(std::ostream &out, c_pprint_opts opts = default_opts) :
    ast::visitor{}, sink{out}, next_label_id{0},
    opts{populate_defaults(std::move(opts))}
  {}

  void emit(const ast::node &node)
  {
    pp_prelude();
    node.accept(*this);
    pp_postlude();
  }

  void accept(const ast::program &prgm) override
  {
    for (auto &node: prgm)
      node.accept(*this);
  }

  void accept(const ast::loop &loop) override
  {
    auto begin_id = get_label();
    auto end_id = get_label();
    pp_label(begin_id);
    pp_bez(end_id);
    for (auto &node: loop)
      node.accept(*this);
    pp_bnz(begin_id);
    pp_label(end_id);
  }

  void accept(const ast::add &node) override
  {
    pp_arith_op("+", node.off(), node.value());
  }

  void accept(const ast::sub &node) override
  {
    pp_arith_op("-", node.off(), node.value());
  }

  void accept(const ast::mul &node) override
  {
    pp_arith_op("*", node.off(), node.value());
  }

  void accept(const ast::mov &node) override
  {
    pp_ptr_op(node.off());
  }

private:

  label_id get_label(void) noexcept
  {
    auto id = next_label_id;
    next_label_id += 1;
    return id;
  }

  void pp_indent(void)
  {
    sink << ' ' << ' ';
  }

  void pp_indent(unsigned long nlevels)
  {
    while (nlevels--)
      pp_indent();
  }

  void pp_vec(const std::vector<std::string> &vec) const
  {
    for (auto &elem: vec)
      sink << elem << std::endl;
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

  void pp_prelude(void) const
  {
    pp_indent();
    pp_vec(prelude);
  }

  void pp_postlude(void) const
  {
    pp_indent();
    pp_vec(prelude);
  }

  void pp_arith_op(const char *op, ptrdiff_t off, bf_value value)
  {
    pp_indent();
    sink << opts.hp_iden << '[' << off << ']' << op << value << ';';
  }

  void pp_ptr_op(ptrdiff_t off)
  {
    pp_indent();
    sink << opts.mov_fn << '(' << off << ')';
  }

  void pp_getc(ptrdiff_t off)
  {
    pp_indent();
    sink << opts.getc_fn << '('
         << opts.hp_iden << '[' << off << ']'
         << ')' << ';' << std::endl;
  }

  void pp_putc(ptrdiff_t off)
  {
    pp_indent();
    sink << opts.putc_fn << '('
         << opts.hp_iden << '[' << off << ']'
         << ')' << ';' << std::endl;
  }

  void pp_mov(ptrdiff_t off)
  {
    pp_indent();
    sink << opts.mov_fn << '('
         << opts.hp_iden << ',' << off
         << ')' << std::endl;
  }

  static c_pprint_opts populate_defaults(c_pprint_opts opts)
  {
    if (opts.prelude.empty())
      opts.prelude = default_opts.prelude;
    if (opts.postlude.empty())
      opts.postlude = default_opts.postlude;
    if (opts.hp_iden.empty())
      opts.hp_iden = default_opts.hp_iden;
    if (opts.mov_fn.empty())
      opts.mov_fn = default_opts.mov_fn;
    if (opts.getc_fn.empty())
      opts.getc_fn = default_opts.getc_fn;
    if (opts.putc_fn.empty())
      opts.putc_fn = default_opts.putc_fn;
    if (opts.label_prefix.empty())
      opts.label_prefix = default_opts.label_prefix;
    return opts;
  }

  label_id next_label_id;
  c_pprint_opts opts;
  static const c_pprint_opts default_opts;

};

}
}

#endif /* !BFC_PPRINT_HPP */
