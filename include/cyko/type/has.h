#ifndef CYKO_TYPE_HAS_H
#define CYKO_TYPE_HAS_H

#include <cyko/meta/expression.h>
#include <cyko/type/none.h>

namespace cyko {
namespace type
{

  /**
   * Use SFINAE to determine if the type _Tp has a publicly-accessible
   * member type _NTYPE.
   */

  #define _GLIBCXX_HAS_NESTED_TYPE(_NTYPE)                        \
  template<typename _Tp, typename = type::none<>>                 \
    struct __has_##_NTYPE                                         \
    : meta::bool_t<false>                                         \
    { };								                                          \
  template<typename _Tp>                                          \
    struct __has_##_NTYPE<_Tp, type::none<typename _Tp::_NTYPE>>  \
    : meta::bool_t<true>                                          \
    { };


} // namespace cyko::type
} // namespace cyko

#endif
