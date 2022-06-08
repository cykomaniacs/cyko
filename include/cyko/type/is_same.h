#ifndef CYKO_TYPE_IS_SAME_H
#define CYKO_TYPE_IS_SAME_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace type
{

  /**
   * @brief Type comparison.
   * @remark Includes const / volatile qualifiers (see example code).
   * @code {.cpp}
   * cyko::type::is_same<int,                int const> // false
   * cyko::type::is_same<int const,          int const> // true
   * cyko::type::is_same<int const volatile, int const> // false
   * @endcode
   */

  template <typename T, typename U>
    struct is_same
    : meta::bool_t<false>
    {
      using self = is_same<T, U>;
    };

  template <typename T>
    struct is_same<T, T>
    : meta::bool_t<true>
    {
      using self = is_same<T, T>;
    };

} // namespace cyko::type
} // namespace cyko

#ifdef CYKO_DEBUG
namespace debug
{
  using namespace cyko::type;

  static_assert(is_same<int,                int const>::negate::value);
  static_assert(is_same<int const,          int const>::value); // true!
  static_assert(is_same<int const volatile, int const>::negate::value);
}
#endif

#endif
