#ifndef CYKO_META_GREATER_H
#define CYKO_META_GREATER_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace meta
{

  template <typename T, typename U>
    struct greater
    : meta::bool_t<(T::value > U::value)>
    {
      using self = greater<T, U>;
    };

} // namespace cyko::meta
} // namespace cyko

#endif
