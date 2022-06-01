#ifndef CYKO_TYPE_IS_POINTER_H
#define CYKO_TYPE_IS_POINTER_H

#include <cyko/meta/expression.h>
#include <cyko/type/remove_cv.h>

namespace cyko {
namespace type {
namespace internal
{

  template <typename T>
    struct is_pointer_help
    : meta::bool_t<false>
    { };

  template <typename T>
    struct is_pointer_help<T*>
    : meta::bool_t<true>
    { };

} // namespace cyko::type::internal

  template <typename T>
    struct is_pointer
    : meta::bool_t<internal::is_pointer_help<type::remove_cv<T>>::value>
    {
      using self = is_pointer<T>;
    };

} // namespace cyko::type
} // namespace cyko

#endif
