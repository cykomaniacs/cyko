#ifndef CYKO_TYPE_IS_UNION_H
#define CYKO_TYPE_IS_UNION_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace type
{

  template <typename T>
    struct is_union
    #ifdef CYKO_BUILD_CODEBASE_MSVC
    : meta::bool_t<__is_union(T)>
    {
      using self = is_union<T>;
    };
    #else
    { static_assert(false, "unimplemented!"); };
    #endif

} // namespace cyko::type
} // namespace cyko

#endif
