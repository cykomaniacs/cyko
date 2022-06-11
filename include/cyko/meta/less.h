#ifndef CYKO_META_LESS_H
#define CYKO_META_LESS_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace meta
{

  template <typename T, typename U>
    struct less
    : meta::bool_t<(T::value < U::value)>
    {
      using self = less<T, U>;
    };

} // namespace cyko::meta
} // namespace cyko

#endif
