#ifndef CYKO_META_MINUS_H
#define CYKO_META_MINUS_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace meta {
namespace internal
{
} // namespace cyko::meta::internal

  template <typename T, typename U>
    struct minus
    : meta::expression<decltype(T::value - U::value), (T::value - U::value)>
    {
      using self = minus<T, U>;
    };

  template <typename T, typename U>
    struct sub
    : meta::expression<decltype(T::value - U::value), (T::value - U::value)>
    {
      using self = sub<T, U>;
    };

} // namespace cyko::meta
} // namespace cyko

#endif
