#ifndef BFC_SOURCELOC_HPP
#define BFC_SOURCELOC_HPP

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>

namespace bfc {

struct source_pos {
  off_t off;
  unsigned long row;
  unsigned long col;
};

std::ostream &
operator<<(std::ostream &out, source_pos pos)
{
  return out << pos.row << ',' << pos.col;
}

class sourceloc {

public:

  sourceloc(source_pos begin, source_pos end, std::string name) noexcept :
    sourceloc{begin, end, std::make_shared<std::string>(std::move(name))}
  {}

  sourceloc(source_pos begin, source_pos end,
             std::shared_ptr<std::string> name) noexcept :
    begin_pos{begin}, end_pos{end}, source_name{name}
  {}

  source_pos begin(void) const noexcept
  {
    return begin_pos;
  }

  source_pos end(void) const noexcept
  {
    return end_pos;
  }

  const std::string &name(void) const noexcept
  {
    return *source_name;
  }

  sourceloc with_pos(source_pos begin, source_pos end) const noexcept
  {
    return sourceloc{begin, end, source_name};
  }

  void print(std::ostream &out) const
  {
    out << *source_name << ':' << begin_pos << '-' << end_pos;
  }

private:

  std::shared_ptr<std::string> source_name;
  source_pos begin_pos;
  source_pos end_pos;

};

std::ostream &
operator<<(std::ostream &out, const sourceloc &loc)
{
  loc.print(out);
  return out;
}

}

#endif /* !BFC_SOURCELOC_HPP */
