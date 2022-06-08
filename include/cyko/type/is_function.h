#ifndef CYKO_TYPE_IS_FUNCTION_H
#define CYKO_TYPE_IS_FUNCTION_H

#include <cyko/meta/och.h>
#include <cyko/type/is_const.h>
#include <cyko/type/is_reference.h>

namespace cyko {
namespace type
{

  /**
   * Only function and reference types can't be const-qualified!
   */

  template <typename T>
    struct is_function
    : meta::och<typename type::is_const<T const>::negate, typename type::is_reference<T>::negate>
    {
      using self = is_function<T>;
    };


} // namespace cyko::type
} // namespace cyko

#endif
