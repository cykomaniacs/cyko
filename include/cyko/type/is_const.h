#ifndef CYKO_TYPE_IS_CONST_H
#define CYKO_TYPE_IS_CONST_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace type
{

  template <typename T>
    struct is_const
    : meta::bool_t<false>
    {
      using self = is_const<T>;
    };

  template <typename T>
    struct is_const<T const>
    : meta::bool_t<true>
    {
      using self = is_const<T const>;
    };

} // namespace cyko::type
} // namespace cyko

#endif
