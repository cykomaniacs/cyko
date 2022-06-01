#ifndef CYKO_META_PLUS_H
#define CYKO_META_PLUS_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace meta {
namespace internal
{
} // namespace cyko::meta::internal

  template <typename T, typename U>
    struct plus
    : meta::expression<decltype(T::value + U::value), (T::value + U::value)>
    {
      using self = minus<T, U>;
    };

  template <typename T, typename U>
    struct add
    : meta::expression<decltype(T::value + U::value), (T::value + U::value)>
    {
      using self = minus<T, U>;
    };

} // namespace cyko::meta
} // namespace cyko

#endif
