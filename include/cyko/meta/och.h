#ifndef CYKO_META_OCH_H
#define CYKO_META_OCH_H

#include <cyko/meta/conditional.h>

namespace cyko {
namespace meta {
namespace internal
{

  template <typename...>
    struct och_help;

  template <typename T, typename... Tail>
    struct och_help<T, Tail...>
    : meta::conditional<T, och_help<Tail...>, meta::bool_t<false>>
    { };

  template <typename T>
    struct och_help<T>
    : meta::bool_t<T::value>
    { };

  template <>
    struct och_help<>
    : meta::bool_t<true>
    { };

} // namespace cyko::meta::internal

  template <typename... T>
    struct och
    : meta::bool_t<internal::och_help<T...>::value>
    {
      using self = och<T...>;
    };

} // namespace cyko::meta
} // namespace cyko

#endif
