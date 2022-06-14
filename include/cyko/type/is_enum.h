#ifndef CYKO_TYPE_IS_ENUM_H
#define CYKO_TYPE_IS_ENUM_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace type
{

  /**
   * Type @b T is a enumurator type?
   *
   * @tparam T The type to check.
   */
  template <typename T>
    struct is_enum
    #if defined(CYKO_BUILD_CXX_MSVC) \
     || defined(CYKO_BUILD_CXX_GCC) \
     || defined(CYKO_BUILD_CXX_LLVM)
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
