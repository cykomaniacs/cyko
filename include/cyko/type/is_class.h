#ifndef CYKO_TYPE_IS_CLASS_H
#define CYKO_TYPE_IS_CLASS_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace type
{

  template <typename T>
    struct is_class
    #ifdef CYKO_BUILD_CODEBASE_MSVC
    : meta::bool_t<__is_class(T)>
    {
      using self = is_class<T>;
    };
    #else
    { static_assert(false, "unimplemented!"); };
    #endif


} // namespace cyko::type
} // namespace cyko

#endif