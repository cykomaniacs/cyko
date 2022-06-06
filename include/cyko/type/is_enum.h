#ifndef CYKO_TYPE_IS_ENUM_H
#define CYKO_TYPE_IS_ENUM_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace type
{

  template <typename T>
    struct is_enum
    #ifdef CYKO_BUILD_TOOLKIT_MSVC
    : meta::bool_t<__is_enum(T)>
    {
      using self = is_enum<T>;
    };
    #elif  CYKO_BUILD_TOOLKIT_LLVM
    : meta::bool_t<__is_enum(T)>
    {
      using self = is_enum<T>;
    };
    #else
    { static_assert(false, "unimplemented!"); };
    #endif

} // namespace cyko::type
} // namespace cyko

#endif
