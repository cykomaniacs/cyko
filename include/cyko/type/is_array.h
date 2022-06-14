#ifndef CYKO_TYPE_IS_ARRAY_H
#define CYKO_TYPE_IS_ARRAY_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace type {
namespace internal
{

  template <typename T>
    struct is_array_impl
    : meta::bool_t<false>
    { };

  template <typename T>
    struct is_array_impl<T[]>
    : meta::bool_t<true>
    { };

  template <typename T, size_t I>
    struct is_array_impl<T[I]>
    : meta::bool_t<true>
    { };

} // namespace cyko::type::internal

  /**
   * Type @b T is an array type?
   *
   * @tparam T The type to check.
   */
  template <typename T>
    struct is_array
    : meta::bool_t<internal::is_array_impl<T>::value>
    {
      using self = is_array<T>;
    };

} // namespace cyko::type
} // namespace cyko

#endif
