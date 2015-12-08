#ifndef BFC_PPRINT_CPP_HPP
#define BFC_PPRINT_CPP_HPP

#include "ast.hpp"
#include "pprint/sink.hpp"

#include <ostream>
#include <string>
#include <vector>

namespace bfc {
namespace pprint {

template <class printer_type>
struct pprint_traits {
  void emit(const printer_type &pp,
            std::ostream &out, const ast::node &node) const {
    pp.emit(out, node);
  }
};

class c_pprint {

public:

  struct config {
    config();
    std::vector<std::string> prelude;
    std::vector<std::string> postlude;
    std::string label_prefix;
    std::string hp_iden;
    std::string mov_iden;
    std::string getc_iden;
    std::string putc_iden;
    std::string add_iden;
    std::string sub_iden;
    std::string mul_iden;
    /* std::string set_iden; */
  };

  c_pprint(void);
  explicit c_pprint(config opts);
  void emit(std::ostream &out, const ast::node &node);

private:

  config opts;

};

}
}

#endif /* !BFC_PPRINT_CPP_HPP */
