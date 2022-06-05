#ifndef CYKO_TYPE_IS_FUNCTION_H
#define CYKO_TYPE_IS_FUNCTION_H

#include <cyko/meta/expression.h>
#include <cyko/meta/negate.h>
#include <cyko/meta/och.h>
#include <cyko/type/is_const.h>
#include <cyko/type/is_reference.h>

/*
template <class _Ty>
_INLINE_VAR constexpr bool is_function_v = // only function types and reference types can't be const qualified
    !is_const_v<const _Ty> && !is_reference_v<_Ty>;
ž/äö*/

namespace cyko {
namespace type
{
//: meta::bool_t<meta::och<meta::negate<type::is_const<T>>, meta::negate<type::is_reference<T>>>::value>
  template <typename T>
    struct is_function
    : meta::negate<type::is_const<T>>::template och<meta::negate<type::is_function<T>>
    {
      using self = is_function<T>;
    };

} // namespace cyko::type
} // namespace cyko

#endif
