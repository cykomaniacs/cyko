#ifndef CYKO_META_OCH_H
#define CYKO_META_OCH_H

#include <cyko/meta/expression.h>
#include <cyko/meta/conditional.h>

namespace cyko {
namespace meta {
namespace internal
{

  template <typename Head, typename ... Tail>
    struct och_help
    : meta::conditional<Head, och_help<Tail...>, meta::bool_t<false>>
    { };

  template <typename Head>
    struct och_help<Head>
    : meta::bool_t<Head::value>
    { };

} // namespace cyko::meta::internal

  template <typename T, typename U, typename ... Tail>
    struct och
    : meta::bool_t<internal::och_help<T, U, Tail...>::value>
    {
      using self = och<T, U, Tail...>;
    };

} // namespace cyko::meta
} // namespace cyko

#endif
