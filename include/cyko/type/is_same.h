#ifndef CYKO_TYPE_IS_SAME_H
#define CYKO_TYPE_IS_SAME_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace type {
namespace internal
{

  template <typename T, typename U>
    struct is_same_help
    : meta::bool_t<false>
    { };

  template <typename T>
    struct is_same_help<T, T>
    : meta::bool_t<true>
    { };

} // namespace cyko::type::internal

  template <typename T, typename U>
    struct is_same
    : meta::bool_t<internal::is_same_help<type::remove_cv<T>, type::remove_cv<U>>::value>
    {
      using self = is_same<T, U>;
    };

} // namespace cyko::type
} // namespace cyko

#endif
