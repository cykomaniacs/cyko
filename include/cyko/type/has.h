#ifndef CYKO_TYPE_HAS_H
#define CYKO_TYPE_HAS_H

#include <cyko/meta/expression.h>
#include <cyko/type/none.h>

namespace cyko {
namespace type
{

  /**
   * Use SFINAE to determine if the type _Tp has a publicly-accessible
   * member type _NTYPE.
   */

  /**
   * COPY/PASTE SFINAE
   */

  // NOLINTNEXTLINE(*macro*)
  #define __HAS_NESTED_TYPE(__T) \
  template<typename T, typename = type::none<>> \
    struct has_##__T \
    : meta::bool_t<false> \
    { }; \
  template<typename T> \
    struct has_##__T<T, type::none<typename T::__T>>  \
    : meta::bool_t<true> \
    { };

  __HAS_NESTED_TYPE(tag)

} // namespace cyko::type
} // namespace cyko

#endif
