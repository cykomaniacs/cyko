#ifndef CYKO_META_EQUAL_H
#define CYKO_META_EQUAL_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace meta
{

  template <typename T, typename U>
    struct equal
    : meta::bool_t<(T::value == U::value)>
    {
      using self = equal<T, U>;
    };

} // namespace cyko::meta
} // namespace cyko

#endif
