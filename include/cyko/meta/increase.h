#ifndef CYKO_META_INCREASE_H
#define CYKO_META_INCREASE_H

#include <cyko/meta/expression.h>
#include <cyko/meta/plus.h>

namespace cyko {
namespace meta
{

  template <typename T>
    struct increase
    : meta::plus<T, meta::int_t<1>>
    {
      using self = increase<T>;
    };

} // namespace cyko::meta
} // namespace cyko

#endif
