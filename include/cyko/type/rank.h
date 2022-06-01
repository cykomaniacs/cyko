#ifndef CYKO_TYPE_RANK_H
#define CYKO_TYPE_RANK_H

#include <cyko/meta/expression.h>
#include <cyko/meta/plus.h>

namespace cyko {
namespace type
{

  /**
   * @brief The number dimensions of an array type.
   */

  template <typename T>
    struct rank
    : meta::size_t<0>
    { };

  template <typename T>
    struct rank<T[]>
    : meta::size_t<1>::plus<rank<T>>
    { };

  template <typename T, cyko::size_t I>
    struct rank<T[I]>
    : meta::size_t<1>::plus<rank<T>>
    { };

} // namespace cyko::type
} // namespace cyko

#endif
