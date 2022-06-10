#ifndef CYKO_META_INCREASE_H
#define CYKO_META_INCREASE_H

#include <cyko/meta/expression.h>
#include <cyko/meta/plus.h>

namespace cyko {
namespace meta
{

  template <typename T>
    struct increase
    : meta::int_t<1>::plus<T>
    {
      using self = increase<T>;
    };

} // namespace cyko::meta
} // namespace cyko

#endif
