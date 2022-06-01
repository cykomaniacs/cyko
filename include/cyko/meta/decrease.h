#ifndef CYKO_META_DECREASE_H
#define CYKO_META_DECREASE_H

#include <cyko/meta/expression.h>
#include <cyko/meta/minus.h>

namespace cyko {
namespace meta
{

  template <typename T>
    struct decrease
    : meta::minus<T, meta::int_t<1>>
    {
      using self = increase<T>;
    };

} // namespace cyko::meta
} // namespace cyko

#endif
