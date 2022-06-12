#ifndef CYKO_TYPE_IS_BASE_OF_H
#define CYKO_TYPE_IS_BASE_OF_H

#include <cyko/meta/expression.h>

namespace cyko {
namespace type
{

  /**
   * @tparam B The base type.
   * @tparam D The derived type.
   */

  template <typename B, typename D>
    struct is_base_of
    #if defined(CYKO_BUILD_CXX_MSVC) \
     || defined(CYKO_BUILD_CXX_GCC) \
     || defined(CYKO_BUILD_CXX_LLVM)
    : meta::bool_t<__is_base_of(B, D)>
    {
      using self = is_base_of<B, D>;
    };
    #else
    { static_assert(false, "unimplemented!"); };
    #endif


} // namespace cyko::type
} // namespace cyko

#endif
