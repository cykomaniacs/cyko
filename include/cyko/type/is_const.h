#ifndef CYKO_TYPE_IS_CONST_H
#define CYKO_TYPE_IS_CONST_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace type
{

  /**
   * Type @b T is const qualified?
   *
   * @tparam T The type to check.
   */
  template <typename T>
    struct is_const
    : meta::bool_t<false>
    {
      using self = is_const<T>;
    };

  template <typename T>
    struct is_const<T const>
    : meta::bool_t<true>
    {
      using self = is_const<T const>;
    };

} // namespace cyko::type
} // namespace cyko

#ifdef CYKO_DEBUG
#include <type_traits>
namespace debug
{
  using namespace ::cyko::type;

  static_assert(is_const<std::add_const_t<int>>::value);
}
#endif

#endif
