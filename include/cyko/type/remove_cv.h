#ifndef CYKO_TYPE_REMOVE_CV_H
#define CYKO_TYPE_REMOVE_CV_H

#include <cyko/type/remove_const.h>
#include <cyko/type/remove_volatile.h>

namespace cyko {
namespace type
{

  /**
   * @brief Removes the top-level @b const and / or @b volatile qualifiers from a type.
   * @see The example code.
   * @code {.cpp}
   * cyko::type::remove_cv<int   const volatile>   // int
   * cyko::type::remove_cv<int   const volatile&&> // int const volatile&&
   * cyko::type::remove_cv<int   const volatile&>  // int const volatile&
   * cyko::type::remove_cv<int   const volatile*>  // int const volatile*
   * cyko::type::remove_cv<int*  const volatile>   // int*
   * cyko::type::remove_cv<int&  volatile>   // int&
   * cyko::type::remove_cv<int&& volatile>   // int&&
   * @endcode
   * @tparam T The type.
   */

  template <typename T>
    using remove_cv = type::remove_const<type::remove_volatile<T>>;

} // namespace cyko::type
} // namespace cyko

#endif
