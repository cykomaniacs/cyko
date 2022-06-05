#ifndef CYKO_TYPE_IS_VOLATILE_H
#define CYKO_TYPE_IS_VOLATILE_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace type
{

  template <typename T>
    struct is_volatile
    : meta::bool_t<false>
    {
      using self = is_volatile<T>;
    };

  template <typename T>
    struct is_volatile<T volatile>
    : meta::bool_t<true>
    {
      using self = is_volatile<T volatile>;
    };

} // namespace cyko::type
} // namespace cyko

#endif
