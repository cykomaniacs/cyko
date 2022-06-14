#ifndef CYKO_TYPE_IS_RVALUE_REFERENCE_H
#define CYKO_TYPE_IS_RVALUE_REFERENCE_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace type
{

  /**
   * Type @b T is an @e rvalue reference?
   *
   * @tparam T The type to check.
   */
  template <typename T>
    struct is_rvalue_reference
    : meta::bool_t<false>
    {
      using self = is_rvalue_reference<T>;
    };

  template <typename T>
    struct is_rvalue_reference<T&&>
    : meta::bool_t<true>
    {
      using self = is_rvalue_reference<T&&>;
    };

} // namespace cyko::type
} // namespace cyko

#endif
