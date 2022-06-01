#ifndef CYKO_META_ELLER_H
#define CYKO_META_ELLER_H

#include <cyko/meta/expression.h>
#include <cyko/meta/conditional.h>

namespace cyko {
namespace meta {
namespace internal
{

  template <typename Head, typename... Tail>
    struct eller_help
    : meta::conditional<Head, meta::bool_t<true>, eller_help<Tail...>>
    { };

  template <typename Head>
    struct eller_help<Head>
    : meta::bool_t<Head::value>
    { };

} // namespace cyko::meta::internal

  template <typename T, typename U, typename... Tail>
    struct eller
    : meta::bool_t<internal::eller_help<T, U, Tail...>::value>
    { };

} // namespace cyko::meta
} // namespace cyko

#endif
