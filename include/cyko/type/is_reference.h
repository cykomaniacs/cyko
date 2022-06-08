#ifndef CYKO_TYPE_IS_REFERENCE_H
#define CYKO_TYPE_IS_REFERENCE_H

#include <cyko/meta/eller.h>
#include <cyko/type/is_lvalue_reference.h>
#include <cyko/type/is_rvalue_reference.h>

namespace cyko {
namespace type
{

  template <typename T>
    struct is_reference
    : meta::eller<
      type::is_lvalue_reference<T>,
      type::is_rvalue_reference<T>>
    {
      using self = is_reference<T>;
    };

} // namespace cyko::type
} // namespace cyko

#endif
