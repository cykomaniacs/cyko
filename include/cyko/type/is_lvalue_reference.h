#ifndef CYKO_TYPE_IS_LVALUE_REFERENCE_H
#define CYKO_TYPE_IS_LVALUE_REFERENCE_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace type
{

  /**
   * Type @b T is an @e lvalue reference?
   *
   * @tparam T The type to check.
   */
  template <typename T>
    struct is_lvalue_reference
    : meta::bool_t<false>
    {
      using self = is_lvalue_reference<T>;
    };

  template <typename T>
    struct is_lvalue_reference<T&>
    : meta::bool_t<true>
    {
      using self = is_lvalue_reference<T&>;
    };

} // namespace cyko::type
} // namespace cyko

#endif
