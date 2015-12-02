#ifndef BFC_PPRINT_SINK_HPP
#define BFC_PPRINT_SINK_HPP

#include <ostream>
#include <system_error>

namespace bfc {
namespace pprint {

class sink_wrapper {

public:

  explicit sink_wrapper(std::ostream &sink) noexcept : sink{&sink}
  {
    auto state = this->sink->rdstate();
    exn_mask = this->sink->exceptions();
    auto new_mask = exn_mask | std::ios::badbit | std::ios::failbit;
    this->sink->exceptions(new_mask);
    this->sink->setstate(state);
  }

  sink_wrapper(const sink_wrapper &other) = delete;

  ~sink_wrapper(void)
  {
    auto state = sink->rdstate();
    sink->exceptions(exn_mask);
    try {
      sink->setstate(state);
    } catch (...) {
      /* swallow any stream failures since we're likely unwinding as a
       * consequence of them (or something worse) anyway
       */
    }
  }

  operator std::ostream &(void) noexcept
  {
    return *sink;
  }

  operator const std::ostream &(void) const noexcept
  {
    return *sink;
  }

  template <class T>
  sink_wrapper &operator<<(const T &value)
  {
    try {
      sink << value;
    } catch (const std::ios_base::failure &exn) {
      on_error();
    }
    return *this;
  }

private:

  void on_error(void) const
  {
    static const char msg[] = "c_pprint: write to stream failed";
    auto code = std::error_code{errno, std::system_category()};
    throw std::system_error{code, msg};
  }

  std::ios::iostate exn_mask;
  std::ostream *sink; /* we use a pointer to avoid copying woes */

};

}
}


#endif /* !BFC_PPRINT_SINK_HPP */
