#ifndef CYKO_TYPE_IS_BASE_OF_H
#define CYKO_TYPE_IS_BASE_OF_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace type
{

  /**
   * Type @b T is the base of type @b U ?
   *
   * @tparam T The base type.
   * @tparam U The derived type.
   */
  template <typename T, typename U>
    struct is_base_of
    #if defined(CYKO_BUILD_CXX_MSVC) \
     || defined(CYKO_BUILD_CXX_GCC) \
     || defined(CYKO_BUILD_CXX_LLVM)
    : meta::bool_t<__is_base_of(T, U)>
    {
      using self = is_base_of<T, U>;
    };
    #else
    { static_assert(false, "unimplemented!"); };
    #endif

} // namespace cyko::type
} // namespace cyko

#endif
