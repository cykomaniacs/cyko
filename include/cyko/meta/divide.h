#ifndef CYKO_META_DIVIDE_H
#define CYKO_META_DIVIDE_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace meta {
namespace internal
{
} // namespace cyko::meta::internal

  template <typename T, typename U>
    struct divide
    : meta::expression<decltype(T::value / U::value), (T::value / U::value)>
    {
      using self = divide<T, U>;
    };

} // namespace cyko::meta
} // namespace cyko

#endif
