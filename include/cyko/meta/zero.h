#ifndef CYKO_META_ZERO_H
#define CYKO_META_ZERO_H

#include <cyko/meta/equal.h>

namespace cyko {
namespace meta
{

  template <typename T>
    struct zero
    : meta::equal<T, meta::int_t<0>>
    {
      using self = zero<T>;
    };

} // namespace cyko::meta
} // namespace cyko

#endif
