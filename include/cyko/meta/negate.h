#ifndef CYKO_META_NEGATE_H
#define CYKO_META_NEGATE_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace meta {
namespace internal
{
} // namespace cyko::meta::internal

  template <typename T>
    struct negate
    : meta::bool_t<!T::value>
    {
      using self = negate<T>;
    };

} // namespace cyko::meta
} // namespace cyko

#endif
