#ifndef CYKO_TYPE_IS_OBJECT_H
#define CYKO_TYPE_IS_OBJECT_H

#include <cyko/meta/eller.h>
#include <cyko/type/is_function.h>
#include <cyko/type/is_reference.h>
#include <cyko/type/is_void.h>

namespace cyko {
namespace type
{

  template <typename T>
    struct is_object
    : meta::eller<
      type::is_function<T>,
      type::is_reference<T>,
      type::is_void<T>>::negate
    {
      using self = is_object<T>;
    };

} // namespace cyko::type
} // namespace cyko

#endif
