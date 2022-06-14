#ifndef CYKO_META_ELLER_H
#define CYKO_META_ELLER_H

#include <cyko/meta/expression.h>
#include <cyko/meta/conditional.h>

namespace cyko {
namespace meta {
namespace internal
{

  template <typename...>
    struct eller_help;

  template <typename T, typename... Tail>
    struct eller_help<T, Tail...>
    : meta::conditional<T, meta::bool_t<true>, eller_help<T, Tail...>>
    { };

  template <typename T>
    struct eller_help<T>
    : meta::bool_t<T::value>
    { };

  template <>
    struct eller_help<>
    : meta::bool_t<false>
    { };

} // namespace cyko::meta::internal

  template <typename... T>
    struct eller
    : meta::bool_t<internal::eller_help<T...>::value>
    { };

} // namespace cyko::meta
} // namespace cyko


namespace cyko {
namespace meta {
namespace internal
{
  /// @b impl @e decl

  template </*typename T, */typename... Tail>
    struct disjunction_impl;

  /// @b impl @e spec

  template <typename T, typename... Tail>
    struct disjunction_impl<T, Tail...>
    : meta::conditional<T, T, disjunction_impl<Tail...>>
    { };

  template <typename T>
    struct disjunction_impl<T>
    : T
    { };

}

  template <typename... T>
    struct discjunction
    : meta::bool_t<internal::disjunction_impl<meta::bool_t<false>, T...>::value>
    {
      using self = discjunction<T...>;
    };

}
}
#endif
