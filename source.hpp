#ifndef BFC_SOURCE_HPP
#define BFC_SOURCE_HPP

#include <cstdio>
#include <istream>
#include <memory>
#include <utility>

namespace bfc {

template <class T>
struct source_traits {

  using source_type = T;

  static int next(source_type &source) noexcept
  {
    return source.next();
  }

  static int peek(source_type &source) noexcept
  {
    return source.peek();
  }

  static bool eof(const source_type &source) noexcept
  {
    return source.eof();
  }

  static bool error(const source_type &source) noexcept
  {
    return source.error();
  }

  static void clear(source_type &source) noexcept
  {
    source.clear();
  }
};

enum class destruct_action {
  destroy,
  release
};

/* Probably a good idea to keep these inlined in the header since we want
 * the operations to be fast.
 */

class stream_source {

public:

  using source_type = std::istream;

  constexpr stream_source(void) noexcept :
    source(nullptr), on_destruct(destruct_action::destroy)
  {}

  explicit stream_source(
      source_type *source,
      destruct_action on_destruct = destruct_action::destroy) noexcept :
    source(source), on_destruct(on_destruct)
  {
    disable_exns();
  }

  stream_source(const stream_source &other) = delete;
  stream_source &operator=(const stream_source &other) = delete;

  stream_source(stream_source &&other) noexcept
    : source(std::move(other.source)), on_destruct(other.on_destruct)
  {}

  stream_source &operator=(stream_source &&other) noexcept
  {
    reset(other.release(), other.on_destruct);
    return *this;
  }

  void swap(stream_source &other) noexcept
  {
    using std::swap;
    source.swap(other.source);
    swap(on_destruct, other.on_destruct);
  }

  ~stream_source(void)
  {
    reset();
  }

  int
  next(void) noexcept
  {
    return source->get();
  }

  int
  peek(void) noexcept
  {
    return source->peek();
  }

  bool
  eof(void) const noexcept
  {
    return source->eof();
  }

  bool
  error(void) const noexcept
  {
    return source->bad() || source->fail();
  }

  void
  clear(void) noexcept
  {
    source->clear();
  }

  source_type *release(void) noexcept
  {
    return source.release();
  }

  void reset(
      source_type *source = nullptr,
      destruct_action on_destruct = destruct_action::destroy) noexcept
  {
    if (this->on_destruct == destruct_action::release)
      release();
    this->source.reset(source);
    this->on_destruct = on_destruct;
  }

private:

  void
  disable_exns(void) noexcept
  {
    if (source)
      source->exceptions(std::ios::goodbit);
  }

  std::unique_ptr<source_type> source;
  destruct_action on_destruct;

};

class file_source {

  struct file_deleter {
    void operator()(FILE *fp) const noexcept
    {
      if (fp)
        std::fclose(fp);
    }
  };

public:

  using source_type = FILE;

  constexpr file_source(void) noexcept :
    source(nullptr), on_destruct(destruct_action::destroy)
  {}

  explicit file_source(
      source_type *source,
      destruct_action on_destruct = destruct_action::destroy) noexcept :
    source(source), on_destruct(on_destruct)
  {}

  file_source(const file_source &other) = delete;
  file_source &operator=(const file_source &other) = delete;

  file_source(file_source &&other) noexcept
    : source(std::move(other.source)), on_destruct(other.on_destruct)
  {}

  file_source &operator=(file_source &&other) noexcept
  {
    reset(other.release(), other.on_destruct);
    return *this;
  }

  void swap(file_source &other) noexcept
  {
    using std::swap;
    source.swap(other.source);
    swap(on_destruct, other.on_destruct);
  }

  ~file_source(void)
  {
    reset();
  }

  int
  next(void) noexcept
  {
    return getc(source.get());
  }

  int
  peek(void) noexcept
  {
    int ch = next();
    if (ch != EOF)
      ungetc(ch, source.get());
    return ch;
  }

  bool
  eof(void) const noexcept
  {
    return feof(source.get());
  }

  bool
  error(void) const noexcept
  {
    return ferror(source.get());
  }

  void
  clear(void) noexcept
  {
    clearerr(source.get());
  }

  source_type *release(void) noexcept
  {
    return source.release();
  }

  void reset(
      source_type *source = nullptr,
      destruct_action on_destruct = destruct_action::destroy) noexcept
  {
    if (this->on_destruct == destruct_action::release)
      release();
    this->source.reset(source);
    this->on_destruct = on_destruct;
  }

private:

  /* Note: mutable since feof and ferror do not accept a const argument yet
   *       also do not change FILE state.
   */
  mutable std::unique_ptr<source_type> source;
  destruct_action on_destruct;

};

}

#endif /* !BFC_SOURCE_HPP */
